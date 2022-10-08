// Taken from https://github.com/zsrtp/GC-Randomizer/blob/stable/include/patch.h
#pragma once

#include <stdint.h>
#include "libtp_c/include/dolphin/os/OSCache.h"
#include "rels/include/cxx.h"

void writeBranch(void* ptr, void* destination);
void writeBranchLR(void* ptr, void* destination);
void writeBranchBL(void* ptr, void* destination);
void writeBranchMain(void* ptr, void* destination, uint32_t branch);
void writeAbsoluteBranch(void* ptr, void* destination);

/**
 * @brief Hooks a function to execute the provided one instead.
 *
 * The trampoline is a callable structure that allows to execute the original function.
 *
 * @param function		The original function to hook.
 * @param destination	The function to replace the hooked function.
 * @return	A pointer to the allocated trampoline.
 */
template <typename Func, typename Dest>
Func hookFunction(Func function, Dest destination, bool absoluteBranch) {
    uint32_t* instructions = reinterpret_cast<uint32_t*>(function);
    uint32_t instructionCount;
    uint32_t* trampoline;

    if (absoluteBranch) {
        instructionCount = 5;
        trampoline = new (sizeof(uint32_t)) uint32_t[instructionCount];
    } else {
        instructionCount = 2;
#ifdef PLATFORM_WII
        trampoline = new (sizeof(uint32_t), HEAP_ZELDA) uint32_t[instructionCount];
#else
        trampoline = new (sizeof(uint32_t)) uint32_t[instructionCount];
#endif
    }

    // Original instruction
    trampoline[0] = instructions[0];
    DCFlushRange(&trampoline[0], sizeof(uint32_t));
    ICInvalidateRange(&trampoline[0], sizeof(uint32_t));

    // Branch to original function past hook
    writeBranch(&trampoline[1], &instructions[1]);

    // Write actual hook
    writeBranch(&instructions[0], reinterpret_cast<void*>(static_cast<Func>(destination)));

    // Branch to original function past hook
    if (absoluteBranch) {
        writeAbsoluteBranch(&trampoline[1], &instructions[1]);
    } else {
        writeBranch(&trampoline[1], &instructions[1]);
    }

    return reinterpret_cast<Func>(trampoline);
}

template <typename Func, typename Dest>
Func hookFunction(Func function, Dest destination) {
    return hookFunction(function, destination, false);
}

template <typename Func, typename Dest>
Func hookFunctionAbsolute(Func function, Dest destination) {
    return hookFunction(function, destination, true);
}

template <typename Func>
Func unhookFunction(Func trampoline) {
    if (!trampoline) {
        return nullptr;
    }

    uint32_t* instructions = reinterpret_cast<uint32_t*>(trampoline);
    uint32_t instructionCount;
    uint32_t* address;

    uint32_t firstInstruction = instructions[1];
    if ((firstInstruction >> 16) == 0x3D80) {  // lis r12
        // Absolute branch
        instructionCount = 5;
        uint32_t instructionAddress = (firstInstruction & 0xFFFF) << 16;  // Upper 16 bits
        instructionAddress |= (instructions[2] & 0xFFFF);                 // Lower 16 bits
        address = reinterpret_cast<uint32_t*>(instructionAddress - 0x4);
    } else {
        // Standard branchinstructionCount = 2;
        int32_t branchLength = firstInstruction & 0x03FFFFFC;

        // Check if this is a negative branch
        if (branchLength > 0x01FFFFFC) {
            const int32_t Width = 26;
            const int32_t Mask = (1 << (Width - 1));
            branchLength = (branchLength ^ Mask) - Mask - 0x4;
        }

        uint32_t instructionAddress = reinterpret_cast<uint32_t>(&instructions[1]);
        address = reinterpret_cast<uint32_t*>(instructionAddress + branchLength);
    }

    *address = instructions[0];

    // Clear the cache for both the address and where the instructions were stored
    DCFlushRange(address, sizeof(uint32_t));
    ICInvalidateRange(address, sizeof(uint32_t));
    DCFlushRange(instructions, sizeof(uint32_t) * instructionCount);
    ICInvalidateRange(instructions, sizeof(uint32_t) * instructionCount);

    // Free the memory used by the trampoline
    delete[] instructions;
    return nullptr;
}

// Taken from https://github.com/zsrtp/GC-Randomizer/blob/stable/source/patch.cpp
#include "rels/include/patch.h"
#include "libtp_c/include/dolphin/os/OSCache.h"
#include <stdint.h>

void writeBranch(void* ptr, void* destination) {
    uint32_t branch = 0x48000000;  // b
    writeBranchMain(ptr, destination, branch);
}

void writeBranchLR(void* ptr, void* destination) {
    uint32_t branch = 0x48000001;  // bl
    writeBranchMain(ptr, destination, branch);
}

void writeBranchBL(void* ptr, void* destination) {
    uint32_t branch = 0x48000001;  // bl
    writeBranchMain(ptr, destination, branch);
}

void writeBranchMain(void* ptr, void* destination, uint32_t branch) {
    uint32_t delta = reinterpret_cast<uint32_t>(destination) - reinterpret_cast<uint32_t>(ptr);

    branch |= (delta & 0x03FFFFFC);

    uint32_t* p = reinterpret_cast<uint32_t*>(ptr);
    *p = branch;

    DCFlushRange(ptr, sizeof(uint32_t));
    ICInvalidateRange(ptr, sizeof(uint32_t));
}

void writeAbsoluteBranch(void* ptr, void* destination) {
    uint32_t dstRaw = reinterpret_cast<uint32_t>(destination);
    uint32_t* code = reinterpret_cast<uint32_t*>(ptr);

    code[0] = 0x3D800000 | (dstRaw >> 16);     // lis r12,dstRaw@h
    code[1] = 0x618C0000 | (dstRaw & 0xFFFF);  // ori r12,r12,dstRaw@l
    code[2] = 0x7D8903A6;                      // mtctr r12
    code[3] = 0x4E800420;                      // bctr

    DCFlushRange(ptr, sizeof(uint32_t) * 4);
    ICInvalidateRange(ptr, sizeof(uint32_t) * 4);
}

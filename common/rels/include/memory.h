/** @file memory.h
 * @author PistonMiner
 * @brief Memory Functions
 *
 * @bug No known bugs
 */
#ifndef LIBTP_MEMORY_H
#define LIBTP_MEMORY_H

#include <cstddef>
#include <cstdint>

void* clearMemory(void* ptr, size_t size);
void clear_DC_IC_Cache(void* ptr, uint32_t size);
#endif
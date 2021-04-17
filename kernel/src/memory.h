#pragma once

#include <stdint.h>
#include <stddef.h>
#include "efiMemory.h"

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize);
void memVectorCopy(uint64_t *dest, uint64_t *src, unsigned long length);


//void memset(void* start, uint8_t value, uint64_t num);
extern "C" void memset(void* buffer, unsigned char value, unsigned long count);
extern "C" void memset16(void* buffer, unsigned short value, unsigned long count);
extern "C" void memset32(void* buffer, unsigned int value, unsigned long count);
extern "C" void memset64(void* buffer, unsigned long value, unsigned long count);

extern "C" void memcpy(void *dest, void *src, unsigned long length);
extern "C" void memcpy16(void *dest, void *src, unsigned long length);
extern "C" void memcpy32(void *dest, void *src, unsigned long length);
extern "C" void memcpy64(void *dest, void *src, unsigned long length);





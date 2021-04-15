#pragma once

#include <stdint.h>
#include "efiMemory.h"

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize);
//void memset(void* start, uint8_t value, uint64_t num);
extern "C" void memset(void* buffer, unsigned char value, unsigned long count);
extern "C" void memset32(void* buffer, unsigned int value, unsigned long count);
extern "C" void memset16(void* buffer, unsigned short value, unsigned long count);

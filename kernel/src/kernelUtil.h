#pragma once

#include <stdint.h>
#include "rendering/BasicRenderer.h"
#include "utils/cstr.h"
#include "efi/efiMemory.h"
#include "memory/memory.h"
#include "utils/maps/Bitmap.h"
#include "paging/PageFrameAllocator.h"
#include "paging/PageMapIndexer.h"
#include "paging/paging.h"
#include "paging/PageTableManager.h"
#include "userinput/mouse.h"
#include "acpi/acpi.h"
#include "pci/pci.h"

struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
	ACPI::RSDP2* rsdp;
	uint32_t* logoImage;
} ;

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo {
    PageTableManager* pageTableManager;
};

KernelInfo InitializeKernel(BootInfo* BootInfo);
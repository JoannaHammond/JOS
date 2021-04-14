#pragma once
#include "paging.h"

class PageTableManager {
    public:
    PageTableManager(PageTable* PML4Address);
    PageTable* PML4;
    void MapMemory(void* virtualMemory, void* physicalMemory, uint8_t pat);
    void MapMemory(void* virtualMemory, void* physicalMemory);
};

#define PAT_WC_MODE 2

extern PageTableManager g_PageTableManager;
extern "C" void CreatePAT();
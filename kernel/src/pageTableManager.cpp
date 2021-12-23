#include "include/pageTableManager.h"
#include "include/pageMapIndexer.h"
#include "include/pageFrameAllocator.h"
#include "include/memory.h"
#include <stdint.h>

PageTableManager::PageTableManager(PageTable* PML4Address)
{
	PML4 = PML4Address;
}

void PageTableManager::mapMemory(void* virtualMemory, void* physicalMemory)
{
	PageMapIndexer indexer((uint64_t)virtualMemory);
	PageDirectoryEntry PDE = PML4->entries[indexer.PDP_index];

	PageTable* PDP;

	if (!PDE.GetFlag(PT_Flag::Present))
	{
		PDP = (PageTable*)globalAllocator.RequestPage();
		memset(PDP, 0, 0x1000);
		PDE.SetAddress((uint64_t)PDP >> 12);
		PDE.SetFlag(PT_Flag::Present, true);
		PDE.SetFlag(PT_Flag::ReadWrite, true);
		PML4->entries[indexer.PDP_index] = PDE;
	}
	else PDP = (PageTable*)((uint64_t)PDE.GetAddress() << 12);

	PDE = PDP->entries[indexer.PD_index];

	PageTable* PD;

	if (!PDE.GetFlag(PT_Flag::Present))
	{
		PD = (PageTable*)globalAllocator.RequestPage();
		memset(PD, 0, 0x1000);
		PDE.SetAddress((uint64_t)PD >> 12);
		PDE.SetFlag(PT_Flag::Present, true);
		PDE.SetFlag(PT_Flag::ReadWrite, true);
		PDP->entries[indexer.PD_index] = PDE;
	}
	else PD = (PageTable*)((uint64_t)PDE.GetAddress() << 12);

	PDE = PD->entries[indexer.PT_index];

	PageTable* PT;

	if (!PDE.GetFlag(PT_Flag::Present))
	{
		PT = (PageTable*)globalAllocator.RequestPage();
		memset(PT, 0, 0x1000);
		PDE.SetAddress((uint64_t)PT >> 12);
		PDE.SetFlag(PT_Flag::Present, true);
		PDE.SetFlag(PT_Flag::ReadWrite, true);
		PD->entries[indexer.PT_index] = PDE;
	}
	else PT = (PageTable*)((uint64_t)PDE.GetAddress() << 12);

	PDE = PT->entries[indexer.P_index];

	PDE.SetAddress((uint64_t)physicalMemory >> 12);
	PDE.SetFlag(PT_Flag::Present, true);
	PDE.SetFlag(PT_Flag::ReadWrite, true);
	PT->entries[indexer.P_index] = PDE;
}
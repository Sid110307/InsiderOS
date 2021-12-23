#include "include/pageMapIndexer.h"

PageMapIndexer::PageMapIndexer(uint64_t virtualAddress)
{
	virtualAddress >>= 12;
	P_index = virtualAddress & 0x1FF;

	virtualAddress >>= 9;
	PT_index = virtualAddress & 0x1FF;

	virtualAddress >>= 9;
	PD_index = virtualAddress & 0x1FF;
	
	virtualAddress >>= 9;
	PDP_index = virtualAddress & 0x1FF;
}
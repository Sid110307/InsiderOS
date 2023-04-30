#include "include/interrupts/IDT.h"

void IDTDescEntry::SetOffset(uint64_t offset)
{
	offsetLow = (uint16_t)(offset & 0x000000000000FFFF);
	offsetMedium = (uint16_t)((offset & 0x00000000FFFF0000) >> 16);
	offsetHigh = (uint32_t)((offset & 0xFFFFFFFF00000000) >> 32);
}

uint64_t IDTDescEntry::GetOffset()
{
	uint64_t offset = 0;

	offset |= (uint64_t)offsetLow;
	offset |= (uint64_t)offsetMedium << 16;
	offset |= (uint64_t)offsetHigh << 32;

	return offset;
}

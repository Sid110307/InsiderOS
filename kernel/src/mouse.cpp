#include "include/hardware/mouse.h"

void MouseWait()
{
	uint64_t timeout = 100000;

	while (timeout--)
		if (inByte(0x64) & 1) return;
}

void MouseWaitInput()
{
	uint64_t timeout = 100000;

	while (timeout--)
		if (inByte(0x64) & 0) return;
}

void InitPS2Mouse()
{
	outByte(0x64, 0xA8);
	MouseWait();

	outByte(0x64, 0x20);
	MouseWaitInput();

	uint8_t status = inByte(0x60);
	status |= 0b10;
	MouseWait();

	outByte(0x64, 0x60);
	MouseWait();

	outByte(0x60, status);
}

#include "include/interrupts/interrupts.h"

void PageFaultHandler(interruptFrame* frame)
{
	Panic("Page Fault Detected!");
	while (true);
}

void DoubleFaultHandler(interruptFrame* frame)
{
	Panic("Double Faults Detected!");
	while (true);
}

void GeneralProtectionFaultHandler(interruptFrame* frame)
{
	Panic("General Protection Fault (Segfault) Detected!");
	while (true);
}

void KeyboardInterruptHandler(interruptFrame* frame)
{
	uint8_t scancode = inByte(0x60);
	handleKeyboardEvent(scancode);
	PICEndMaster();
}

void MouseInterruptHandler(interruptFrame* frame)
{
	GlobalRenderer->Print("Mouse!");
	GlobalRenderer->NextLine();

	PICEndSlave();
}

void RemapPIC()
{
	uint8_t a1, a2;

	a1 = inByte(PIC1_DATA);
	IOWait();
	a2 = inByte(PIC2_DATA);
	IOWait();

	outByte(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	IOWait();
	outByte(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	IOWait();

	outByte(PIC1_DATA, 0x20);
	IOWait();
	outByte(PIC2_DATA, 0x28);
	IOWait();

	outByte(PIC1_DATA, 4);
	IOWait();
	outByte(PIC2_DATA, 2);
	IOWait();

	outByte(PIC1_DATA, ICW4_8086);
	IOWait();
	outByte(PIC2_DATA, ICW4_8086);
	IOWait();

	outByte(PIC1_DATA, a1);
	IOWait();
	outByte(PIC2_DATA, a2);
}

void PICEndMaster()
{
	outByte(PIC1_COMMAND, PIC_EOI);
}

void PICEndSlave()
{
	outByte(PIC2_COMMAND, PIC_EOI);
	outByte(PIC1_COMMAND, PIC_EOI);
}
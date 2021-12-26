#pragma once

#include "../basicRenderer.h"
#include "../panic.h"
#include "../hardware/IO.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21

#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

#define PIC_EOI 0x20

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01


struct interruptFrame;
__attribute__((interrupt)) void PageFaultHandler(struct interruptFrame* frame);
__attribute__((interrupt)) void DoubleFaultHandler(struct interruptFrame* frame);
__attribute__((interrupt)) void GeneralProtectionFaultHandler(struct interruptFrame* frame);

__attribute__((interrupt)) void KeyboardInterruptHandler(struct interruptFrame* frame);

void RemapPIC();
void PICEndMaster();
void PICEndSlave();
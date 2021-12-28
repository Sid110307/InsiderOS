#pragma once

#include <stdint.h>

namespace QWERTYKeyboard
{

#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define SPACE 0x39

	extern const char ASCIITable[];
	char Translate(uint8_t scancode, bool isUppercase);
}
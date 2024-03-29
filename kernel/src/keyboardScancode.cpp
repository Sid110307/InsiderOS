#include "include/hardware/keyboardScancode.h"

namespace QWERTYKeyboard {
	const char ASCIITable[] = {
		0, 0, '1', '2', '3', '4',
		'5', '6', '7', '8', '9',
		'0', '-', '=', 0, 0,
		'q', 'w', 'e', 'r', 't',
		'y', 'u', 'i', 'o', 'p',
		'[', ']', 0, 0, 'a',
		's', 'd', 'f', 'g', 'h',
		'j', 'k', 'l', ';', '\'',
		'`', 0, '\\', 'z', 'x',
		'c', 'v', 'b', 'n', 'm',
		',', '.', '/', 0, '*',
		0, ' '
	};

	char Translate(uint8_t scancode, bool isUppercase) {
		if (scancode >= 58) return 0;
		return isUppercase ? ASCIITable[scancode] - 32 : ASCIITable[scancode];
	}
}
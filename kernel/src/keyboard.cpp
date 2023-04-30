#include "include/hardware/keyboard.h"

bool isLeftShiftPressed = false;
bool isRightShiftPressed = false;

void handleKeyboardEvent(uint8_t scancode)
{

	switch (scancode)
	{
	case LEFT_SHIFT:
		isLeftShiftPressed = true;
		return;
	case LEFT_SHIFT + 0x80:
		isLeftShiftPressed = false;
		return;
	case RIGHT_SHIFT:
		isRightShiftPressed = true;
		return;
	case RIGHT_SHIFT + 0x80:
		isRightShiftPressed = false;
		return;
	case ENTER:
		GlobalRenderer->NextLine();
		return;
	case SPACE:
		GlobalRenderer->DrawChar(' ');
		return;
	case BACKSPACE:
		GlobalRenderer->ClearChar();
		return;
	}

	char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed | isRightShiftPressed);
	if (ascii != 0) GlobalRenderer->DrawChar(ascii);
}
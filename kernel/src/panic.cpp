#include "include/panic.h"

void Panic(const char* message)
{
	GlobalRenderer->Clear(COLOR_DARK_CYAN);
	GlobalRenderer->cursorPosition = { 0, 0 };
	GlobalRenderer->Color = COLOR_DARK_RED;
	GlobalRenderer->NextLine();
	GlobalRenderer->Print("##      ##   ##      ##          ########    ##      ##   ##");
	GlobalRenderer->NextLine();
	GlobalRenderer->Print("##      ##   ##      ##         ##      ##   ##      ##   ##");
	GlobalRenderer->NextLine();
	GlobalRenderer->Print("##      ##   ##########         ##      ##   ##########   ##");
	GlobalRenderer->NextLine();
	GlobalRenderer->Print("##      ##   ##      ##         ##      ##   ##      ##");
	GlobalRenderer->NextLine();
	GlobalRenderer->Print("##########   ##      ##          ########    ##      ##   ##");
	GlobalRenderer->NextLine();
	GlobalRenderer->NextLine();
	GlobalRenderer->NextLine();
	GlobalRenderer->Print(message);
	GlobalRenderer->NextLine();
	GlobalRenderer->NextLine();
	GlobalRenderer->Print("Your system has encountered a fatal error.");
	GlobalRenderer->NextLine();
	GlobalRenderer->Print("Hang on while we try to fix it.");
}
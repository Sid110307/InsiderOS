#pragma once

#include <stdint.h>

#include "../lib/math.h"
#include "../lib/colors.h"
#include "../lib/framebuffer.h"
#include "../lib/basicfonts.h"

class BasicRenderer
{
public:
	BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* targetFont);

	Point cursorPosition;
	Framebuffer* TargetFramebuffer;
	PSF1_FONT* TargetFont;

	unsigned int Color;
	unsigned int ClearColor;

	void DrawChar(char chr, unsigned int xOffset, unsigned int yOffset);
	void DrawChar(char chr);

	void Print(const char* str);
	void NextLine();

	void ClearChar();
	void Clear();
};

extern BasicRenderer* GlobalRenderer;
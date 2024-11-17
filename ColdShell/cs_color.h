#ifndef zs_color
#define zs_color

#include <windows.h>
void SetColor(int foreground, int background=0)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), background * 16 + foreground);
}

enum Color {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15,
};
#endif
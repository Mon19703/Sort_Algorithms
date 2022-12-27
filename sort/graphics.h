#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <math.h>
#include <windows.h>
#include <Windows.h>
#include "stack.h"
#define LENGTH 40
#define RED RGB(255,0,0)
#define WHITE RGB(255,255,255)
#define BLACK RGB(0,0,0)
const COLORREF rgbRed = 0x000000FF;
const COLORREF rgbGreen = 0x0000FF00;
const COLORREF rgbBlue = 0x00FF0000;
const COLORREF rgbBlack = 0x00000000;
const COLORREF rgbWhite = 0x00FFFFFF;
using namespace std;

HPEN  getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF);
BOOL  SetPoint(HDC hDC, HPEN hPen, COORD PNT);
BOOL  PlotLine(HDC hDC, HPEN hPen, COORD BGN, COORD END);
BOOL  PlotRect(HDC hDC, HPEN hPen, COORD BGN, COORD END);
BOOL  PlotCirc(HDC hDC, HPEN hPen, COORD BGN, COORD END);
COORD setCordScale(COORD POS, RECT pRECT);
void ShowCur(bool CursorVisibility);

HDC hDC;
HPEN PEN;
HANDLE StdOut;
WORD COLOR;
COORD BGN, POS;

short mov;
short movx;

void initgraph(void)
{
	system("cls");
	mov = 30;
	movx = 0;
	HWND hWnd = GetForegroundWindow();
	RECT    pRECT = { 0 };
	COORD   POS1 = { 0 };
	COORD   BGN1 = setCordScale(POS1, pRECT);
	GetWindowRect(hWnd, &pRECT);
	hDC = GetWindowDC(hWnd);
	PEN = getPen(PS_SOLID, 2, RGB(255, 255, 255));
	StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ShowCur(false);
}

void changey(int value) { if (value > -1000 & value < 1000) mov = (short)value; }
void changex(int value) { if (value > -1000 & value < 1000) movx = (short)value; }
int getmaxx(void) { return 640; }
int getmaxy(void) { return 300; }

wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
void drawText(int x, int y, int z, int t, char* mess) {
	RECT rect;
	LPCWSTR message = convertCharArrayToLPCWSTR(mess);
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);
	GetWindowRect(console_handle, &rect);

	//Here's a 5 pixels wide RED line [from initial 0,0] to 300,300
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	SelectObject(device_context, pen);
	SetTextColor(device_context, WHITE);
	SetBkMode(device_context, TRANSPARENT);
	rect.left = x;
	rect.top = y;
	rect.right = z;
	rect.bottom = t;
	DrawText(device_context, message, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	ReleaseDC(console_handle, device_context);
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}


void setcolorRGB(int r, int g, int b)
{
	PEN = getPen(PS_SOLID, 2, RGB(r, g, b));
}
void setcolor(int color)
{
	if (color < 0) color = -color;
	if (color > 15) color %= 16;
	switch (color)
	{
	case 0: PEN = getPen(PS_SOLID, 2, RGB(0, 0, 0)); break;
	case 1: PEN = getPen(PS_SOLID, 2, RGB(0, 0, 128)); break;
	case 2: PEN = getPen(PS_SOLID, 2, RGB(0, 128, 0)); break;
	case 3: PEN = getPen(PS_SOLID, 2, RGB(128, 0, 0)); break;
	case 4: PEN = getPen(PS_SOLID, 2, RGB(0, 128, 128)); break;
	case 5: PEN = getPen(PS_SOLID, 2, RGB(128, 0, 128)); break;
	case 6: PEN = getPen(PS_SOLID, 2, RGB(128, 128, 0)); break;
	case 7: PEN = getPen(PS_SOLID, 2, RGB(0, 0, 255)); break;
	case 8: PEN = getPen(PS_SOLID, 2, RGB(0, 255, 0)); break;
	case 9: PEN = getPen(PS_SOLID, 2, RGB(255, 0, 0)); break;
	case 10: PEN = getPen(PS_SOLID, 2, RGB(0, 255, 255)); break;
	case 11: PEN = getPen(PS_SOLID, 2, RGB(255, 0, 255)); break;
	case 12: PEN = getPen(PS_SOLID, 2, RGB(255, 255, 0)); break;
	case 13: PEN = getPen(PS_SOLID, 2, RGB(192, 192, 192)); break;
	case 14: PEN = getPen(PS_SOLID, 2, RGB(192, 192, 192)); break;
	case 15: PEN = getPen(PS_SOLID, 2, RGB(255, 255, 255)); break;
	}
}

void setfontcolor(int color)
{
	if (color < 0) color = -color;
	if (color > 15) color %= 16;
	switch (color)
	{
	case 0: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); COLOR = COMMON_LVB_REVERSE_VIDEO; break;
	case 1: COLOR = (FOREGROUND_BLUE); break;
	case 2: COLOR = (FOREGROUND_GREEN); break;
	case 3: COLOR = (FOREGROUND_RED); break;
	case 4: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN); break;
	case 5: COLOR = (FOREGROUND_BLUE | FOREGROUND_RED); break;
	case 6: COLOR = (FOREGROUND_GREEN | FOREGROUND_RED); break;
	case 7: COLOR = (FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
	case 8: COLOR = (FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
	case 9: COLOR = (FOREGROUND_RED | FOREGROUND_INTENSITY); break;
	case 10: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
	case 11: COLOR = (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY); break;
	case 12: COLOR = (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); break;
	case 13: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); break;
	case 14: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | COMMON_LVB_REVERSE_VIDEO); break;
	case 15: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | COMMON_LVB_REVERSE_VIDEO | FOREGROUND_INTENSITY); break;
	}
	SetConsoleTextAttribute(StdOut, COLOR);
}



void line(int x1, int y1, int x2, int y2)
{
	BGN.X = (short)x1 + movx;
	BGN.Y = (short)y1 + mov;
	POS.X = (short)x2 + movx;
	POS.Y = (short)y2 + mov;
	PlotLine(hDC, PEN, BGN, POS);
}

void square(int x, int y)
{
	line(x, y, x + LENGTH, y);
	line(x, y, x, y + LENGTH);
	line(x + LENGTH, y, x + LENGTH, y + LENGTH);
	line(x, y + LENGTH, x + LENGTH, y + LENGTH);
}


void putpixel(int x, int y)
{
	line(x, y, x, y);
}

void circle(int x, int y, int radius)
{
	BGN.X = (short)x + movx - radius / 2;
	BGN.Y = (short)y + mov - radius / 2;
	POS.X = (short)x + movx + radius / 2;
	POS.Y = (short)y + mov + radius / 2;
	PlotCirc(hDC, PEN, BGN, POS);
}

void rectangle(int x1, int y1, int x2, int y2)
{
	BGN.X = (short)x1 + movx;
	BGN.Y = (short)y1 + mov;
	POS.X = (short)x2 + movx;
	POS.Y = (short)y2 + mov;
	PlotRect(hDC, PEN, BGN, POS);
}

void gotoxy(int x, int y)
{
	BGN.X = (short)x;
	BGN.Y = (short)y;
	SetConsoleCursorPosition(StdOut, BGN);
}

void outtextxy(int x, int y, string text)
{
	gotoxy(x / 8, y / 12);
	std::cout << text;
}

void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void cls()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	// Scroll the rectangle of the entire buffer.
	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;

	// Scroll it upwards off the top of the buffer with a magnitude of the entire height.
	scrollTarget.X = 0;
	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

	// Fill with empty spaces with the buffer's default text attribute.
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes = csbi.wAttributes;

	// Do the scroll
	ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

	// Move the cursor to the top left corner too.
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}


HPEN getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF)
{
	return CreatePen(iPEN_STYLE, iPEN_SIZE, iCOLORREF);
}

BOOL SetPoint(HDC hDC, HPEN hPen, COORD PNT)
{
	EXTLOGPEN pINFO;
	GetObject(hPen, sizeof(EXTLOGPEN), &pINFO);
	SelectObject(hDC, hPen);
	return Ellipse
	(
		hDC,
		PNT.X - pINFO.elpWidth,
		PNT.Y + pINFO.elpWidth,
		PNT.X + pINFO.elpWidth,
		PNT.Y - pINFO.elpWidth
	);
}

BOOL PlotLine(HDC hDC, HPEN hPen, COORD BGN, COORD END)
{
	SelectObject(hDC, hPen);
	MoveToEx(hDC, BGN.X, BGN.Y, NULL);
	return LineTo(hDC, END.X, END.Y);
}

BOOL PlotRect(HDC hDC, HPEN hPen, COORD BGN, COORD END)
{
	SelectObject(hDC, hPen);
	return Rectangle(hDC, BGN.X, BGN.Y, END.X, END.Y);
}

BOOL  PlotCirc(HDC hDC, HPEN hPen, COORD BGN, COORD END)
{
	SelectObject(hDC, hPen);
	return Ellipse(hDC, BGN.X, BGN.Y, END.X, END.Y);
}

COORD setCordScale(COORD POS, RECT pRECT)
{
	if (POS.X == 0)
		POS.X = 1;
	if (POS.Y == 0)
		POS.Y = 1;

	int nROWS = 25;
	int nCOLS = 80;

	double CX = (pRECT.right - pRECT.left) / nCOLS;
	double CY = (pRECT.bottom - pRECT.top) / nROWS;

	//При текстовом режиме(text mode) экран  делится  на  ячейки
	//(80  или 40 колонок в ширину и 25 строк в высоту)
	POS.X *= CX;
	POS.Y *= CY;

	int xBORDER = GetSystemMetrics(SM_CXBORDER);//Ширина границы окна
	int yBORDER = GetSystemMetrics(SM_CYMENU);  //Высота заголовка окна ~= высоте строк меню
	int xDRAG = GetSystemMetrics(SM_CXDRAG);  //Число пикселей на гориз дрожение мыши
	int yDRAG = GetSystemMetrics(SM_CYDRAG);  //Число пикселей на вертик дрожение мыши

	POS.X += xBORDER + xDRAG;//Ширина границы окна + число пикселей на дрожение мыши
	POS.Y += yBORDER + yDRAG;
	return POS;
}

COLORREF color(int color)
{
	switch (color) {
	case 1: return rgbBlack;
	case 2: return rgbRed;
	case 3: return rgbGreen;
	case 4: return rgbBlue;
	default: return rgbWhite;
	}
}

void FrameRectangle(int x1, int y1, int x2, int y2, int A)
{
	RECT rect;
	HWND hwd = GetForegroundWindow();
	HDC hdc = GetDC(hwd);
	HBRUSH hBrush = CreateSolidBrush(color(A));
	rect.left = x1;
	rect.top = y1;
	rect.right = x2;
	rect.bottom = y2;
	FrameRect(hdc, &rect, hBrush);
}

void arrow(int x, int y)
{
	line(x, y, x - 10, y + 10);
	line(x, y, x, y + 20);
	line(x, y, x + 10, y + 10);
}

void DrawStack()
{
	line(200, 30, 200, 100);
	line(300, 30, 250, 100);
}
#endif


#pragma once
#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <Windows.h>
#include <locale.h>

enum colors { black, blue, green, red = 4, white = 7, stress };

class Console {
public:
	Console() {
		SetConsoleOutputCP(936);		// 默认代码页936（简体中文）
		hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	Console(unsigned CodePage) {
		SetConsoleOutputCP(CodePage);	// 设置代码页 (如英语：437)
		hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	~Console() {
		static bool isClosed = false;
		if(!isClosed)
			isClosed = CloseHandle(hOutput);
	}
	CONSOLE_SCREEN_BUFFER_INFO info() {	// 返回控制台窗口信息
		CONSOLE_SCREEN_BUFFER_INFO bInfo;
		GetConsoleScreenBufferInfo(hOutput, &bInfo);
		return bInfo;
	}
	SMALL_RECT position() {				// 返回控制台窗口位置坐标
		return info().srWindow;
	}
	COORD buffer() {					// 返回控制台缓冲区大小
		return info().dwSize;
	}
	wchar_t* title() {			// 返回控制台窗口标题
		wchar_t* cTitle = new wchar_t [255];
		GetConsoleTitle(cTitle, 255);
		return cTitle;
	}

#ifdef _INC_LOCALE
	char* locale() {					// 返回控制台程序地区信息
		return setlocale(LC_ALL, "");
	}
	Console& locale(const char* Locale) {	// 设置控制台程序地区信息
		setlocale(LC_ALL, Locale);
		return *this;
	}
#endif /*_INC_LOCALE*/

	Console& title(const wchar_t* Title) {	// 设定控制台窗口标题
		SetConsoleTitle(Title);
		return *this;
	}
	Console& position(short Left,short Top,
		 short Right, short Bottom) {		// 设置控制台窗口位置坐标
		SMALL_RECT rc = { Left,Top,Right,Bottom };
		SetConsoleWindowInfo(hOutput, true, &rc);
		return *this;
	}
	Console& buffer(short X, short Y) {		// 设置控制台缓冲区大小
		COORD dSize = { X, Y };
		SetConsoleScreenBufferSize(hOutput, dSize);
		return *this;
	}
	Console& size(short X, short Y) {		// 设置控制台窗口大小
		buffer(X + 1, Y + 1);
		SMALL_RECT rc = { 0, 0, X, Y };
		SetConsoleWindowInfo(hOutput, true, &rc);
		return *this;
	}
	Console& color(unsigned short Color) {	// 设置输出流文本颜色
		SetConsoleTextAttribute(hOutput, Color);
		//Color为十六进制数：第一位背景色，第2位前景色
		return *this;
	}
	Console& color(unsigned short Back, unsigned short Front) {
		SetConsoleTextAttribute(hOutput, Front | (Back * 16));
		// 与enum colors{black,blue,green,red,white,stress}搭配使用
		// (red, green)红底绿字; (black, red|green) 黑底黄字
		return *this;
	}
	Console& cursor(short X, short Y) {				 // 设置光标所在坐标
		COORD w = { X, Y };
		SetConsoleCursorPosition(hOutput, w);
		return *this;
	}
	Console& cursor(unsigned size, bool visible) {	// 设置光标大小及是否可见
		CONSOLE_CURSOR_INFO cursorInfo = { size, visible };
		SetConsoleCursorInfo(hOutput, &cursorInfo);
		return *this;
	}
	Console& font(short X, short Y) {				// 更改点阵字体大小
		CONSOLE_FONT_INFOEX cfi = {
			sizeof CONSOLE_FONT_INFOEX,
			0, X, Y, FF_DONTCARE, FW_NORMAL
		};
		SetCurrentConsoleFontEx(hOutput, FALSE, &cfi);
		return *this;
	}
	Console& font(const wchar_t* Name, short Size) { // 设置字体及大小
		CONSOLE_FONT_INFOEX cfi = {
			sizeof CONSOLE_FONT_INFOEX,
			0, 0, Size, FF_DONTCARE, FW_NORMAL
		};
		wcscpy_s(cfi.FaceName, Name);
		SetCurrentConsoleFontEx(hOutput, FALSE, &cfi);
		return *this;
	}
	Console& clear() {
		system("cls");
		return *this;
	}
	Console& pause() {
		system("pause");
		return *this;
	}
private:
	HANDLE hOutput;	// 标准输出设备句柄
};

static Console console;

#endif /*_CONSOLE_H*/
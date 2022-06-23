#pragma once
#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <Windows.h>
#include <locale.h>

enum colors { black, blue, green, red = 4, white = 7, stress };

class Console {
public:
	Console() {
		SetConsoleOutputCP(936);		// Ĭ�ϴ���ҳ936���������ģ�
		hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	Console(unsigned CodePage) {
		SetConsoleOutputCP(CodePage);	// ���ô���ҳ (��Ӣ�437)
		hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	~Console() {
		static bool isClosed = false;
		if(!isClosed)
			isClosed = CloseHandle(hOutput);
	}
	CONSOLE_SCREEN_BUFFER_INFO info() {	// ���ؿ���̨������Ϣ
		CONSOLE_SCREEN_BUFFER_INFO bInfo;
		GetConsoleScreenBufferInfo(hOutput, &bInfo);
		return bInfo;
	}
	SMALL_RECT position() {				// ���ؿ���̨����λ������
		return info().srWindow;
	}
	COORD buffer() {					// ���ؿ���̨��������С
		return info().dwSize;
	}
	wchar_t* title() {			// ���ؿ���̨���ڱ���
		wchar_t* cTitle = new wchar_t [255];
		GetConsoleTitle(cTitle, 255);
		return cTitle;
	}

#ifdef _INC_LOCALE
	char* locale() {					// ���ؿ���̨���������Ϣ
		return setlocale(LC_ALL, "");
	}
	Console& locale(const char* Locale) {	// ���ÿ���̨���������Ϣ
		setlocale(LC_ALL, Locale);
		return *this;
	}
#endif /*_INC_LOCALE*/

	Console& title(const wchar_t* Title) {	// �趨����̨���ڱ���
		SetConsoleTitle(Title);
		return *this;
	}
	Console& position(short Left,short Top,
		 short Right, short Bottom) {		// ���ÿ���̨����λ������
		SMALL_RECT rc = { Left,Top,Right,Bottom };
		SetConsoleWindowInfo(hOutput, true, &rc);
		return *this;
	}
	Console& buffer(short X, short Y) {		// ���ÿ���̨��������С
		COORD dSize = { X, Y };
		SetConsoleScreenBufferSize(hOutput, dSize);
		return *this;
	}
	Console& size(short X, short Y) {		// ���ÿ���̨���ڴ�С
		buffer(X + 1, Y + 1);
		SMALL_RECT rc = { 0, 0, X, Y };
		SetConsoleWindowInfo(hOutput, true, &rc);
		return *this;
	}
	Console& color(unsigned short Color) {	// ����������ı���ɫ
		SetConsoleTextAttribute(hOutput, Color);
		//ColorΪʮ������������һλ����ɫ����2λǰ��ɫ
		return *this;
	}
	Console& color(unsigned short Back, unsigned short Front) {
		SetConsoleTextAttribute(hOutput, Front | (Back * 16));
		// ��enum colors{black,blue,green,red,white,stress}����ʹ��
		// (red, green)�������; (black, red|green) �ڵ׻���
		return *this;
	}
	Console& cursor(short X, short Y) {				 // ���ù����������
		COORD w = { X, Y };
		SetConsoleCursorPosition(hOutput, w);
		return *this;
	}
	Console& cursor(unsigned size, bool visible) {	// ���ù���С���Ƿ�ɼ�
		CONSOLE_CURSOR_INFO cursorInfo = { size, visible };
		SetConsoleCursorInfo(hOutput, &cursorInfo);
		return *this;
	}
	Console& font(short X, short Y) {				// ���ĵ��������С
		CONSOLE_FONT_INFOEX cfi = {
			sizeof CONSOLE_FONT_INFOEX,
			0, X, Y, FF_DONTCARE, FW_NORMAL
		};
		SetCurrentConsoleFontEx(hOutput, FALSE, &cfi);
		return *this;
	}
	Console& font(const wchar_t* Name, short Size) { // �������弰��С
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
	HANDLE hOutput;	// ��׼����豸���
};

static Console console;

#endif /*_CONSOLE_H*/
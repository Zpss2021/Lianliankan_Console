#pragma once
#ifndef _MENU_H
#define _MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "Map.h"

using namespace std;

typedef vector<string> options;

class Menu {
public:
	unsigned _Space;
	Menu(options Options);
	void show(bool ordered, bool resume, size_t chosen);
	unsigned getSelect(size_t Min, size_t Max);
	unsigned exec(bool ordered, size_t chosen, string Hint);
	unsigned exec(bool ordered, size_t chosen);
	unsigned exec(bool ordered, string Hint);
	unsigned exec(bool ordered);
private:
	options _Options;
	size_t _Length;
};

static Menu* menu;

extern Menu mainMenu;
extern Menu loadMenu;
extern Menu rankMenu;
extern Menu helpMenu;
extern Menu diffMenu;
extern options setOptions;
extern options* setOpCps;

#endif/*_MENU_H*/
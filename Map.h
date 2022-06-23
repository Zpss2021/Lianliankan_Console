#pragma once

#ifndef _MAP_H
#define _MAP_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <string>
#include "Console.h"
#include "Judge.h"
#include "Menu.h"

using namespace std;

class Map {
public:
	Map(unsigned Level);		// 关卡数：1（4x4）、2（6x6）、3（8x8）
	void init(unsigned Diff);	// 难度：1（6种）、2（9种）、3（12种）
	void sort();
	static const char* toMark(int);
	static const char* toMark(int, bool);
	void print();
	void print(COORD);
	void getCursor();
	void setEmpty();
	void timer(string);
	friend class Level;
private:
	time_t second;
	size_t resort;
protected:
	bool done;
	int emptyed;
	vector<vector<int>> map;
	vector<COORD> coords;
};

inline void wait(unsigned sec) {
	clock_t end = clock() + CLK_TCK * sec;
	while (clock() < end);
}

inline bool isEmpty(int n) {
	return n == -1 ? true : false;
}


#endif	/*_MAP_H*/
#pragma once

#ifndef _MAP_H
#define _MAP_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include "Console.h"
#include "Judge.h"

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
//	unsigned getElementsByCoord(COORD);
//	unsigned getElementsByCoord(unsigned, unsigned);
private:
	vector<vector<int>> map;
	vector<COORD> coords;
};

bool isEmpty(int);

#endif	/*_MAP_H*/
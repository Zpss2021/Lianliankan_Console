#pragma once
#ifndef _JUDGE_H
#define _JUDGE_H

#include <cmath>
#include <cstring>
#include <vector>
#include "Map.h"

using std::vector;

namespace toJudge {
	using std::abs;
	using std::strcmp;
	bool Judge(int** a, int b[4], int size);/*�ж��Ƿ��ܹ�����*/
	bool Two(int** a, int b[4]);/*������*/
	bool Check(int** a, int x, int y, bool c[5]);/*����ĳ���������ҵ����*/
	bool UpDown(int** a, int b[4], int g);
	bool LeftRight(int** a, int b[4], int g);
}

static int** arr;

bool Judge(vector<vector<int>>&, COORD, COORD);

#endif /*_JUDGE_H*/
#include "Map.h"

Map::Map(unsigned Level) {
	size_t Size = size_t(Level) * 2 + 2;
	map.resize(Size);
	for (size_t i = 0; i < Size; i++)
		map[i].resize(Size);
}

void Map::init(unsigned Diff) {
	vector<unsigned> tmp;
	for (unsigned i = 0, num = 3 * Diff + 3;
		i < map.size() * map.size(); i++) {
		tmp.push_back(i % num);
		tmp.push_back(i % num);
	}
	for (size_t i = 0, k = 0; i < map.size(); i++)
		for (size_t j = 0; j < map.size(); j++)
			map[i][j] = tmp[k++];
}

void Map::sort() {
	srand((unsigned)time(NULL));
	for (int i = 0; i < map.size() * map.size(); i++)
		swap(map[rand() % map.size()][rand() % map.size()],
			map[rand() % map.size()][rand() % map.size()]);
}

const char* Map::toMark(int num) {
	switch (num) {
	case -1:
		return "¡¡";
	case 0:
		return "¡î";
	case 1:
		return "¡ï";
	case 2:
		return "¡ð";
	case 3:
		return "¡ñ";
	case 4:
		return "¡ò";
	case 5:
		return "¡ó";
	case 6:
		return "¡ö";
	case 7:
		return "¡Ë";
	case 8:
		return "¡Ñ";
	case 9:
		return "£À";
	case 10:
		return "¡è";
	case 11:
		return "¡ç";
	default:
		return "?";
	}
}

const char* Map::toMark(int num, bool selected) {
	colors bgColor = selected ? stress : black;
	switch (num) {
	case -1:	
		console.color(bgColor, white);
		break;
	case 0:	
		console.color(bgColor, red);
		break;
	case 1:
		console.color(bgColor, red);
		break;
	case 2:	
		console.color(bgColor, green);
		break;
	case 3:	
		console.color(bgColor, green);
		break;
	case 4:	
		console.color(bgColor, white);
		break;
	case 5:	
		console.color(bgColor, white);
		break;
	case 6:	
		console.color(bgColor, red | green);
		break;
	case 7:	
		console.color(bgColor, blue);
		break;
	case 8:	
		console.color(bgColor, blue | green);
		break;
	case 9:
		console.color(bgColor, blue);
		break;
	case 10:
		console.color(bgColor, red | blue);
		break;
	case 11:
		console.color(bgColor, red | green);
		break;
	default:
		console.color(white, black);
		return "?";
	}
	return toMark(num);
}

void Map::print() {
	bool selected;
	console.clear();
	cout.put('\n');
	for (size_t i = 0, k = 0; i < map.size(); i++) {
		cout << "    ";
		for (size_t j = 0; j < map.size(); j++) {
			selected = false;
			for (size_t k = 0; k < coords.size(); k++)
				if (coords[k].Y == i && coords[k].X == j)
					selected = true;
			cout << toMark(map[i][j], selected);
			console.color(black, white);
		}
		cout.put('\n');
	}
}

void Map::print(COORD c) {
	vector<COORD> temp(coords);
	temp.push_back(c);
	bool selected;
	console.clear();
	cout.put('\n');
	for (size_t i = 0, k = 0; i < map.size(); i++) {
		cout << "    ";
		for (size_t j = 0; j < map.size(); j++) {
			selected = false;
			for (size_t k = 0; k < temp.size(); k++)
				if (temp[k].Y == i && temp[k].X == j)
					selected = true;
			cout << toMark(map[i][j], selected);
			console.color(black, white);
		}
		cout.put('\n');
	}
//	cout << '[' << temp[temp.size() - 1].X << "," << temp[temp.size() - 1].Y << ']' << endl;
}

void Map::getCursor() {
	COORD chosed{ 0, 0 };
	bool done = false;
	while (!done) {
P:		print(chosed);
		switch (_getch()) {
		case 'w':case 'W':case 72:
			if (chosed.Y - 1 >= 0)
				chosed.Y--;
			break;
		case 'a':case 'A':case 75:
			if (chosed.X - 1 >= 0)
				chosed.X--;
			break;
		case 's':case 'S':case 80:
			if (size_t(chosed.Y) + 1 < map.size())
				chosed.Y++;
			break;
		case 'd':case 'D':case 77:
			if (size_t(chosed.X) + 1 < map.size())
				chosed.X++;
			break;
		case 13:case' ':
			if (isEmpty(map[chosed.Y][chosed.X]))
				goto P;
			for (vector<COORD>::iterator it = coords.begin(); it != coords.end(); ++it)
				if (it->Y == chosed.Y && it->X == chosed.X) {
					coords.erase(it);
					goto P;
				}
			if (coords.size() < 2)
				coords.push_back(chosed);
			break;
		case 27:
			//need to add function...
			console.clear().pause();
			exit(0);
		case 'r':case'R':
			sort();
			break;
		default:
			break;
		}
		if (coords.size() == 2)	//need to add music...
			if (Judge(map, coords[0], coords[1]))
				setEmpty();
			else
				coords.clear();
		for (size_t i = 0; i < map.size(); i++)
			for (size_t j = 0; j < map[i].size(); j++)
				if (!isEmpty(map[i][j]))
					goto P;
		done = true;
	}
}

void Map::setEmpty() {
	for (vector<COORD>::iterator it = coords.begin(); it != coords.end(); ++it)
		map[it->Y][it->X] = -1;
	coords.clear();
}
//unsigned Map::getElementsByCoord
//	(unsigned x, unsigned y) {
//	return map[x][y];
//}
//
//unsigned Map::getElementsByCoord (COORD n) {
//	return map[n.X][n.Y];
//}

bool isEmpty(int n)
{
	if (n == -1)
		return true;
	return false;
}
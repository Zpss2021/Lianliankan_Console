#include "Game.h"

Map::Map(unsigned Level)
	:second(30 * Level), done(false), over(false), resort(0) {
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
	size_t sz = map.size();
	srand((unsigned)time(NULL));
	for (int i = 0; i < sz * sz; i++)
		swap(map[rand() % sz][rand() % sz],
			map[rand() % sz][rand() % sz]);
	console.clear();
}

const char* Map::toMark(int num) {
	switch (num) {
	case -1:
		return "　";
	case 0:
		return "☆";
	case 1:
		return "★";
	case 2:
		return "○";
	case 3:
		return "●";
	case 4:
		return "◎";
	case 5:
		return "◇";
	case 6:
		return "■";
	case 7:
		return "∷";
	case 8:
		return "⊙";
	case 9:
		return "＠";
	case 10:
		return "¤";
	case 11:
		return "＄";
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
	size_t sz = map.size(), tsz = coords.size();
	bool selected;
	console.clear();
	cout << endl;
	for (size_t i = 0; i < sz; i++) {
		cout << "    ";
		for (size_t j = 0; j < sz; j++) {
			selected = false;
			for (size_t k = 0; k < tsz; k++)
				if (coords[k].Y == i && coords[k].X == j)
					selected = true;
			cout << toMark(map[i][j], selected);
		}
		console.color(black, white);
		cout << endl;
	}
}

void Map::print(COORD c) {
	vector<COORD> temp(coords);
	temp.push_back(c);
	size_t sz = map.size(), tsz = temp.size();
	bool selected;
	console.clear();
	cout << endl;
	for (size_t i = 0; i < sz;i++) {
		cout << "    ";
		for (size_t j = 0; j < sz; j++) {
			selected = false;
			for (size_t k = 0; k < tsz; k++)
				if (temp[k].Y == i && temp[k].X == j)
					selected = true;
			cout << toMark(map[i][j], selected);
		}
		console.color(black, white);
		cout << endl;
	}
}

void Map::getCursor() {
	COORD chosed{ 0, 0 };
	while (!done) {
P:		if (over)
			break;
		else {
		print(chosed);
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
			console.clear();
			cout << "按Esc退出" << endl;
			cout << "其他键继续..." << endl;
			switch(_getch()) {
			case 27:
				console.clear();
				exit(0);
			default:
				break;
			}
			break;
		case 'b':case'B':	////need save and read
			switch (pausMenu.exec(true, 2)) {
			case 1:
				//off the audio, need more...
				break;
			case 2:
				break;
			case 3:
				//save the game, need more...
			case 4:default:
				//need to add function...
				console.clear().pause();
				exit(0);
			}
		case 'r':case'R':
			sort();
			resort++;
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
}

void Map::setEmpty() {
	for (vector<COORD>::iterator it = coords.begin(); it != coords.end(); ++it)
		map[it->Y][it->X] = -1;
	coords.clear();
}

void Map::timer(string cTitle) {
	time_t t, m, s, d, i = 0;
	tm* target;
	string title;
	wchar_t* wt;
	time(&t);
	target = localtime(&t);
	target->tm_min += int(second) / 60;
	target->tm_sec += int(second) % 60;
	t = mktime(target);
	d = time_t(difftime(t, time(NULL)));
	while (d > 0 && !done) {
		second = d = time_t(difftime(t, time(NULL)));
		m = d / 60;
		s = d % 60;
		title = "剩余时间: ";
		if (m < 10)
			title += "0";
		title += to_string(m);
		title += ":";
		if (s < 10)
			title += "0";
		title += to_string(s);
		wt = new wchar_t[title.size()];
		swprintf(wt, title.size(), L"%S", title.c_str());
		console.title(wt);
		delete[] wt;
		if (done)
			return;
		wait(1);
		i++;
		if (d > 10 && i % 4 == 0) {
			wt = new wchar_t[cTitle.size()];
			swprintf(wt, cTitle.size(), L"%S", cTitle.c_str());
			console.title(wt);
			delete[] wt;
			if (done)
				return;
			wait(2);
		}
	}
	over = true;
	return;
}
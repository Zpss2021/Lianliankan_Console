#include "Menu.h"

Menu::Menu(options Options) :_Options(Options), _Space(4), _Length(0) {}
void Menu::show(bool ordered, bool resume, size_t chosen) {
	options opts = _Options;
	size_t i, j;
	string tmp;
	if (resume)
		console.clear();
	if (ordered) 
		for (i = 0; i < opts.size(); i++) {
			tmp = to_string(i + 1);
			tmp += ".";
			opts[i] = tmp + opts[i];
		}
	for (i = 0; i < opts.size(); i++) {
		tmp = Map::toMark(i % 12);
		for (j = 0; j < _Space; j++)
			tmp += " ";
		opts[i] = tmp + opts[i];
	}
	for (i = 1, _Length = opts[0].length(); i < opts.size(); i++)
		if (opts[i].length() > _Length)
			_Length = opts[i].length();

	console.size(short(_Length + _Space + 3), short(_Length / 2 + 1));

	for (i = 0; i < opts.size(); i++) {
		tmp.clear();
		for (j = 0; j < _Length + _Space - opts[i].length(); j++)
			tmp += " ";
		opts[i] = opts[i] + tmp + Map::toMark(i % 12);
	}
	cout.put(' ');
	for (i = 1; i <= (_Length + _Space + 2) / 2; i++)
		cout << Map::toMark(i % 12, false);
	console.color(black, white);
	cout << endl;
	if (--chosen >= 0)
		for (i = 0; i < opts.size(); i++) {
			cout.put(' ');
			if (i == chosen)
				console.color(white, black);
			cout << opts[i] << endl;
			if (i == chosen)
				console.color(black, white);
		}
	else for (i = 0; i < opts.size(); i++)
			cout << "  " << opts[i] << endl;
	cout.put(' ');
	for (i = (_Length + _Space + 2) / 2; i >= 1; i--)
		cout << Map::toMark(i % 12, false);
	console.color(black, white);
	cout << endl;
}
unsigned Menu::getSelect(size_t Min, size_t Max) {
	size_t chosed = Min;
	while (true) switch (_getch()) {
	case 'w':case 'W':case 72:
	case 'a':case 'A':case 75:
		if (chosed != Min)
			show(true, true, --chosed);
		break;
	case 's':case 'S':case 80:
	case 'd':case 'D':case 77:
		if (chosed != Max)
			show(true, true, ++chosed);
		break;
	case 13:case' ':
		return unsigned(chosed);
	case 27:
		console.clear().pause();
		exit(0);
	default:
		break;
	}
}
unsigned Menu::exec(bool ordered, size_t chosen, string Hint) {
	size_t i = 0;
	show(ordered, true, chosen);
	cout << endl;
	for (i = 0; i <= _Length / 2 + _Space - Hint.size() / 2 - 1; i++)
		cout.put(' ');
	cout << Hint;
	return getSelect(1, _Options.size());
}

unsigned Menu::exec(bool ordered, size_t chosen) {
	return exec(ordered, chosen, "");
}

unsigned Menu::exec(bool ordered, string Hint) {
	return exec(ordered, 0, Hint);
}

unsigned Menu::exec(bool ordered) {
	return exec(ordered, "");
}
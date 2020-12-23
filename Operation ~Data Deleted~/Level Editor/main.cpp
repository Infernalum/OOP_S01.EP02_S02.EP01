
#include "Map Editor.h"

void output(const mystd::Table<double>& arr) {
	for (auto iter = arr.begin(); iter != arr.end(); ++iter)
		std::cout << *iter << ' ';
	std::cout << '\n';
}

int main() {
	setlocale(0, "");

	unsigned p;

	std::cin >> p;

	bool pp = std::cin.good();

	Item* t = new AmmoBox;
	Item* tt = new AmmoBox;

	std::fstream file("1.txt", std::ios::in);

	t->load(file);
	t->load(file);

	//mystd::Table<Item*> arr = { t, tt };
	mystd::Table<double> arr = { 2, -3, 4, 3.5 };
	output(arr);
	arr.pop_back();
	arr.push_back(6.66);
	output(arr);
	arr.insert(arr.begin() + 1, -6.66);
	output(arr);
	arr.insert(arr.end() - 1, 0);
	output(arr);
	arr.insert(arr.end(), 123);
	output(arr);
	arr.insert(arr.begin(), -2.5);
	arr.insert(arr.begin(), 0.6);
	output(arr);
	XCom::Level lvl = Editor::Initialization();
	int outcome = 1;
	while (outcome)
		outcome = Editor::Menu(lvl);
	return 0;
}
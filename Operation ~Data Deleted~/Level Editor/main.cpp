
#include "Map Editor.h"

int main() {
	setlocale(0, "");
	Battlefield::Level lvl = Editor::Initialization();
	int outcome = 1;
	while (outcome)
		outcome = Editor::Menu(lvl);
	return 0;
}
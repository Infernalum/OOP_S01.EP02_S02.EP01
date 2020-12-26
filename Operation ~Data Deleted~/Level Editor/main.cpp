
#include "Map Editor.h"
#include <iomanip>
#include <Windows.h>

int (*fptr[])(Level&) = { nullptr, };

int main() {
	srand(time(0));
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Добро пожаловать в редактор карт для приложения \"Operation ~'Data Deleted'\"\n";
	Level level = Editor::Initialization();
	Editor::Menu(level);

	std::fstream savefile("config.txt", std::ios::out);
	level.save(savefile);

	//Creature* basic = nullptr;
	//std::fstream file("1.txt", std::ios::in);
	//int ID;
	//while (!file.eof()) {
	//	for (int i = 0; i < 3; ++i) {
	//		file >> ID;
	//		file.ignore();
	//		switch (ID) {
	//		case CREATUREID_PORTER:
	//			basic = new Porter;
	//			dynamic_cast<Porter*>(basic)->load(file);
	//			std::cout << *basic << '\n';
	//			break;
	//		case CREATUREID_CHRYSSALID:
	//			basic = new Chryssalid;
	//			dynamic_cast<Chryssalid*>(basic)->load(file);
	//			std::cout << *basic << '\n';
	//			break;
	//		case CREATUREID_MUTON:
	//			basic = new Muton;
	//			dynamic_cast<Muton*>(basic)->load(file);
	//			std::cout << *basic << '\n';
	//			break;
	//		}
	//		if (file.eof())
	//			std::cout << "dfsac";
	//	}
	//	// ИБО В КОНЦЕ СТОИТ ЕЩЕ ЛИШНИЙ '\n'!!!!
	//	file.ignore(2);

	//}



	//Porter porter;


	////porter.load(file);
	////std::cout << porter << '\n';


	//Ammo* ammo = new Ammo;
	//ammo->set_type("12х76 мм");
	//Weapon* rifle = new Weapon("Дробовик \"Розочка\"", *ammo);
	//rifle->set_clip(3).set_maxClip(5);
	//rifle->set_scatter(8);
	//AmmoBox* ammobox = new AmmoBox(*ammo);
	//FirstAidKit* aid = new FirstAidKit;
	//aid->set_rec(10).set_qty(1);
	//Weapon* catana = new Weapon("Катана какого-то япошки");
	//catana->set_maxClip(0).set_radius(2).set_scatter(14).set_penalty(0);
	//porter.add_item(rifle).add_item(ammobox).add_item(catana).add_item(aid);

	//std::cout << porter << '\n';


	//Weapon* gra = new Weapon("Гранатомет \"Пушок\"", { "15 мм", 0.850 });
	//gra->set_clip(1).set_maxClip(2).set_damage(75).set_scatter(25);
	//Muton muton(gra);

	//std::cout << muton << '\n';

	//Chryssalid cry;
	//cry.set_x(5);
	//cry.set_y(43);
	//std::cout << cry << '\n';


	////std::fstream file("1.txt", std::ios::out);
	////porter.save(file);
	////muton.save(file);
	////cry.save(file);
	////file.close();

	////mystd::Table<Item*> arr = { t, tt };

	//XCom::Level lvl = Editor::Initialization();
	//int outcome = 1;
	//while (outcome)
	//	outcome = Editor::Menu(lvl);
	return 0;
}
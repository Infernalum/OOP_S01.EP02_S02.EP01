#include "Map Editor.h"

extern const int numCreatures, numMenu, numItems;

namespace Editor {

	// Первая инициализация (задание размера карты и изменение типа клеток)
	XCom::Level Initialization() {
		Level lvl;
		short n, m;
		while (true) {
			try {
				std::cout << "Введите длину карты (в пикселях): ";
				inputType(n, std::cin, std::cout);
				std::cout << "Введите ширину карты (в пикселях): ";
				inputType(m, std::cin, std::cout);
				lvl.set_proportions(n, m);
				break;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << '\n';
			}
		}
		int rc = 0;
		std::cout << "Желаете ввести карту самостоятельно (1), или будете редакторовать её через меню (2)?\n --> ";
		do
			inputType(rc, std::cin, std::cout);
		while (rc < 1 || rc > 2);
		if (rc == 1) {
			std::cout << "Введите карту:\n";
			inputType(lvl, std::cin, std::cout);
			std::cout << "Введена карта:\n" << lvl;
		}
		return lvl;
	}


	/*
	Меню редактора:
	1) Изменить клетку (изменить тип клетки, добавить предмет на клетку, удалить предмет с клетки)
	2) Добавить новое существо;
	3) Изменить какое-то существо;
	*/
	int Menu(Level& lvl) {
		getState(lvl);
		int rc = 1;
		while (rc) {
			std::cout << "Выберите действие:\n 1 - Изменить клетку (изменить тип, добавить/удалить предмет, изменить предмет);\n 2 - Добавить новое существо;\n 3 - Изменить какое-то существо (изменить хар-ки, переставить, удалить);\n 0 - Выход;\n --> ";
			do
				inputType(rc, std::cin, std::cout);
			while (rc > 3 || rc < 0);
			switch (rc) {
			case 0:
				return rc;
				break;
			case 1:
				changeCell(lvl);
				break;
			case 2:
				changeCreature(lvl);
				break;
			case 3:
				changeCreature(lvl);
				break;
			}
			system("cls");
			getState(lvl);
		}
		return rc;
	}


	// Изменение клетки
	void changeCell(Level& lvl) {
		int rc;
		int x, y, type;
		while (true) {
			std::cout << "Введите координату x клетки: ";
			inputType(x, std::cin, std::cout);
			std::cout << "Введите координату y клетки: ";
			inputType(y, std::cin, std::cout);
			std::cout << "Выберите:\n 1 - Изменить тип клетки;\n 2 - Добавить/изменить/удалить предмет;\n 0 - Вернуться в меню;\n --> ";
			do
				inputType(rc, std::cin, std::cout);
			while (rc < 0 || rc > 2);
			switch (rc) {
			case 0:
				break;
			case 1:
				try {
					std::cout << "Выберите тип клетки: \n 1: Пол;\n 2: Стена;\n 3: Стекло;\n 4: Перегородка;\n 5: Складская точка;\n --> ";
					inputType(type, std::cin, std::cout);
					lvl.set_cell(x, y, type);
					getState(lvl);
					std::cout << lvl;
				}
				catch (const std::exception& ex) {
					std::cout << ex.what() << '\n';
				}
				break;
			case 2: {
				Item* item = createItem();
				lvl.acess_to_field()[y][x].add_new_item(item);
				std::cout << "Предмет успешно добавлен!\n";
				break;
			}
			case 3:
				break;
			}
			getState(lvl);
			std::cout << "Продолжить редактирование карты? 1 - Да, 2 - нет: --> \n";
			do
				inputType(rc, std::cin, std::cout);
			while (rc < 1 || rc > 2);
			if (rc == 2)
				return;
		}
	}

	// Изменение существ в командах
	void changeCreature(Level& lvl) {
		while (true) {
			Creature* creature = createCreature();
			std::cout << "Введите координаты существа: -->\n x: ";
			int x;
			inputType(x, std::cin, std::cout);
			std::cout << " y: ";
			int y;
			inputType(y, std::cin, std::cout);
			lvl.add_to_level(creature, x, y);
			std::cout << "Существо успешно добавлено на поле!\n";
			getState(lvl);
			std::cout << "Продолжить редактирование карты? 1 - Да, 2 - нет: --> \n";
			int rc;
			do
				inputType(rc, std::cin, std::cout);
			while (rc < 1 || rc > 2);
			if (rc == 2)
				return;
		}
	}



	// Выбор существа
	/*Creature* answer_1(const std::string msgs[], int N, Creature* ptr, Level& lvl) {
		getState(lvl);
		std::cout << "Пожалуйста, выберите тип существа:\n";
		for (int i = 0; i < N; ++i)
			std::cout << msgs[i] << '\n';
		std::cout << " --> ";
		int ans;
		do
			inputType(ans, std::cin, std::cout);
		while (ans < 0 || ans > N);
		switch (ans) {
		case 0:
			ptr = nullptr;
			break;
		case 1:
			ptr = new Chryssalid;
			break;

		}
		return ptr;
	}*/


	// Выбор номера альтернативы
	int dialog(const std::string msgs[], int N) {
		std::string errmsgs = "";
		int rc, i;
		do {
			std::cout << errmsgs;
			errmsgs = "Ошибка! Повторите ввод!";
			for (i = 0; i < N; ++i)					// Вывод списка альтернатив
				std::cout << (msgs[i]) << "\n";
			printf("Выберите: --> ");
		} while (getType(rc, std::cin) < 0 || rc >= N);
		return rc;
	}


	// Создание нового предмета
	Item* createItem() {
		Item* item = nullptr;
		std::cout << "Выберите предмет: --> \n";
		int res = dialog(Items, numItems);
		if (!res)
			return nullptr;
		switch (res) {
		case ITEMID_AMMOBOX: {
			item = new AmmoBox;

			break;
		};
		case ITEMID_FIRSTAIDKIT: {
			item = new FirstAidKit;

			break;
		};
		case ITEMID_WEAPON: {
			std::string name;
			std::cout << "Введите название оружия: --> ";
			std::getline(std::cin, name);
			item = new Weapon(name);

			break;
		};
		}

		return item;
	}


	// Создание нового существа
	Creature* createCreature() {
		Creature* creature = nullptr;
		std::cout << "Выберите существо: --> \n";
		int res = dialog(Creatures, numCreatures) - 2;
		if (res == -2)
			return nullptr;
		switch (res) {
		case CREATUREID_OPERATIVE: {
			std::string name;
			std::cout << "Введите позывной оперативника: --> ";
			std::getline(std::cin, name);
			creature = new Operative(name);

			break;
		};
		case CREATUREID_PORTER: {
			creature = new Porter;

			break;
		};
		case CREATUREID_CHRYSSALID: {
			creature = new Chryssalid;

			break;
		};
		case CREATUREID_MUTON: {
			creature = new Muton;

			break;
		}
		}

		return creature;
	}


	// Изменение базовых характеристик существа (1 - идем дальше; 0 - удалили существо)
	int answer_2(Creature* ptr, Level& lvl) {
		int ans;
		std::cout << "Выбрано " << *ptr << "\n Измените базовые характеристики:\n 1 - Изменить здоровье;\n 2 - Изменить очки времени;\n 3 - Изменить радиус обзора;\n 4 - Перейти дальше;\n 0 - удалить существо и вернуться в меню;\n --> ";
		do inputType(ans, std::cin, std::cout);
		while (ans < 0 || ans > 4);
		if (!ans) {
			delete ptr;
			system("cls");
			return ans;
		}
		if (ans == 4)
			return 1;
		std::cout << "Введите новое значение параметра: --> ";
		int par;
		inputType(par, std::cin, std::cout);
		switch (ans) {
		case 1:
			try {
				ptr->set_maxHP(par);
				close(lvl);
				std::cout << "Характеристики существа успешно изменены.\n";
			}
			catch (const std::exception& ex) {
				close(lvl);
				std::cout << ex.what() << '\n';
			}
			break;
		case 2:
			try {
				ptr->set_maxTP(par);
				close(lvl);
				std::cout << "Характеристики существа успешно изменены.\n";
			}
			catch (const std::exception& ex) {
				close(lvl);
				std::cout << ex.what() << '\n';
			}
			break;
		case 3:
			try {
				ptr->set_sight(par);
				close(lvl);
				std::cout << "Характеристики существа успешно изменены.\n";
			}
			catch (const std::exception& ex) {
				close(lvl);
				std::cout << ex.what() << '\n';
			}
			break;
		}
		return ans;
	}



	// Получение полной информации по карте
	void getState(Level& lvl) {
		std::cout << "Ваша карта:\n" << lvl << '\n';
	}


	void close(Level& lvl) {
		system("cls");
		getState(lvl);
	}


}
#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include "BattleFieldClass/pch.h"

using namespace XCom;


const std::string Creatures[] = { "0. Вернуться в меню", "1. Оперативник" , "2. Фуражир ", "3. Дикое существо", "4. Разумное существо", };

const int numCreatures = sizeof(Creatures) / sizeof(Creatures[0]);

const std::string Items[] = {"0. Вернуться в меню", "1. Оружейный ящик", "2. Аптечка первой помощи", "3. Оружие" };

const int numItems = sizeof(Items) / sizeof(Items[0]);

const std::string Menu[] = { "0. Выйти", "1. Изменить ландшафт поля" "2. Добавить новое существо на поле", "3. Добавить новые предметы на поле" };

const int numMenu = sizeof(Menu) / sizeof(Menu[0]);


namespace Editor {

	// Загрузка карты из конфига


	int dialog(const std::string msgs[], int N);

	// Выбор существа
	Creature* answer_1(const std::string msgs[], int, Creature*);

	//Creature* answer_1(const std::string msgs[], int, Creature*, Level&);

	// Изменение базовых характеристик существа (1 - идем дальше, 0 - удалили существо)
	int answer_2(Creature&, Level&);

	// Первичная инициализация (задание размера карты)
	Level Initialization();

	// Организация меню редактора карты
	int Menu(Level&);

	// Изменение ландшафта (и предметов на полу)
	void changeCell(Level&);

	// Изменение существ в командах
	void changeCreature(Level&);

	// Создание нового предмета
	Item* createItem();

	// Создание нового существа 
	Creature* createCreature();

	// изменение/удаление старых существ
	void changeCreature(Level&);

	// Получение информации о крате, обо всех существах и обо всех предметах, лежащих на клетках
	void getState(Level&);

	void close(Level&);

}

#endif // !_MAP_EDITOR_H


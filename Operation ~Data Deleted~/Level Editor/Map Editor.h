#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include "BattleFieldClass/pch.h"

using namespace Battlefield;


const std::string Cr[] = { "1. Криссалид", "0. Вернуться в меню" };

const int numCr = sizeof(Cr) / sizeof(Cr[0]);

const std::string Menu[] = { "0. Выйти", "1. Добавить новое существо на поле", "2. Добавить новые предметы на поле / в инвентарь существа", "Изменить/удалить существующее существо" };

const int numMenu = sizeof(Menu) / sizeof(Menu[0]);


namespace Editor {

	// Выбор существа
	Creature* answer_1(const std::string msgs[], int, Creature*);

	// Изменение базовых характеристик существа (1 - идем дальше, 0 - удалили существо)
	int answer_2(Creature&, Level&);

	// Первичная инициализация (задание размера карты)
	Level Initialization();

	// Организация меню редактора карты
	int Menu(Level&);

	// Изменение клетки
	void changeCell(Level&);

	// Создание нового существа (возвращает nullptr при выходе либо указатель на успешно созданное существо)
	void createCreature(Level&);

	// изменение/удаление старых существ
	void changeCreature(Level&);

	// Получение информации о крате, обо всех существах и обо всех предметах, лежащих на клетках
	void getState(const Level&);

	void close(Level&);

}

#endif // !_MAP_EDITOR_H


#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include "BattleFieldClass/pch.h"

using namespace XCom;


const std::string Creatures[] = { "0. ��������� � ����", "1. �����������" , "2. ������� ", "3. ����� ��������", "4. �������� ��������", };

const int numCreatures = sizeof(Creatures) / sizeof(Creatures[0]);

const std::string Items[] = {"0. ��������� � ����", "1. ��������� ����", "2. ������� ������ ������", "3. ������" };

const int numItems = sizeof(Items) / sizeof(Items[0]);

const std::string Menu[] = { "0. �����", "1. �������� �������� ����" "2. �������� ����� �������� �� ����", "3. �������� ����� �������� �� ����" };

const int numMenu = sizeof(Menu) / sizeof(Menu[0]);


namespace Editor {

	// �������� ����� �� �������


	int dialog(const std::string msgs[], int N);

	// ����� ��������
	Creature* answer_1(const std::string msgs[], int, Creature*);

	//Creature* answer_1(const std::string msgs[], int, Creature*, Level&);

	// ��������� ������� ������������� �������� (1 - ���� ������, 0 - ������� ��������)
	int answer_2(Creature&, Level&);

	// ��������� ������������� (������� ������� �����)
	Level Initialization();

	// ����������� ���� ��������� �����
	int Menu(Level&);

	// ��������� ��������� (� ��������� �� ����)
	void changeCell(Level&);

	// ��������� ������� � ��������
	void changeCreature(Level&);

	// �������� ������ ��������
	Item* createItem();

	// �������� ������ �������� 
	Creature* createCreature();

	// ���������/�������� ������ �������
	void changeCreature(Level&);

	// ��������� ���������� � �����, ��� ���� ��������� � ��� ���� ���������, ������� �� �������
	void getState(Level&);

	void close(Level&);

}

#endif // !_MAP_EDITOR_H


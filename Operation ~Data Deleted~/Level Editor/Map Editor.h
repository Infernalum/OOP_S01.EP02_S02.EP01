#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include "BattleFieldClass/pch.h"

using namespace Battlefield;


const std::string Cr[] = { "1. ���������", "0. ��������� � ����" };

const int numCr = sizeof(Cr) / sizeof(Cr[0]);

const std::string Menu[] = { "0. �����", "1. �������� ����� �������� �� ����", "2. �������� ����� �������� �� ���� / � ��������� ��������", "��������/������� ������������ ��������" };

const int numMenu = sizeof(Menu) / sizeof(Menu[0]);


namespace Editor {

	// ����� ��������
	Creature* answer_1(const std::string msgs[], int, Creature*);

	// ��������� ������� ������������� �������� (1 - ���� ������, 0 - ������� ��������)
	int answer_2(Creature&, Level&);

	// ��������� ������������� (������� ������� �����)
	Level Initialization();

	// ����������� ���� ��������� �����
	int Menu(Level&);

	// ��������� ������
	void changeCell(Level&);

	// �������� ������ �������� (���������� nullptr ��� ������ ���� ��������� �� ������� ��������� ��������)
	void createCreature(Level&);

	// ���������/�������� ������ �������
	void changeCreature(Level&);

	// ��������� ���������� � �����, ��� ���� ��������� � ��� ���� ���������, ������� �� �������
	void getState(const Level&);

	void close(Level&);

}

#endif // !_MAP_EDITOR_H


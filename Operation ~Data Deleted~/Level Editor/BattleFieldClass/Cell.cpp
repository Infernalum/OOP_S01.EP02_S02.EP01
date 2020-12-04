#include "pch.h"
#include "Cell.h"





namespace Battlefield {



	/********************************************************/
	/*					������������						*/
	/********************************************************/

	/* ��������!!!! ������ ���������� � ������������ �������������
		��� ��� ����� ������ � ���� ���������� �������������� ��������� (� ������, ���������������) ��������
	���������� ������� ������������ ���, ����� � ������� ����� ���� �������� ��� � ��������� ��������,
	� �� ������ �������� ����. ����� �������� ������� � ��������� ����������� �������, �� ���� �������
	�����, ��� copy- � move- ������������ ������� ����� ����� (��� �������� ���� � ������� � �������� ���
	� main, ��� ����������/�������� � ����/�� ����� � �.�.). �������:
		��� ������ ���������� �����������: �� ���������� ����������� ����� ������.
	�� ���� �� ������� ����� �������� � ����� �� ������ ��������� ���������. � => ���� ��� ������ �������������� � �����������
	��������� �� �������� � ��������.
		��� ������ ������������ �����������: �������� �� ������� (������ ��� ��������� �������), ��� ������ ������������������
		��� ������ ����������: ����� ��� �� �� ������� ����������� ��������, �� ������� ��������� �������� (��� ����� ��� � ���� ������
		���������� � ��� ������ ����� ���)
	*/



	// ����������� �� ���������: ������� ������ ������� "���", ������� ����� � �������� ����� ��� ������ ������
	Cell::Cell() noexcept :
		species(Level::get_sprites()[0]),
		itemList(),
		creature() {};


	// �����������, �������� ��� ������� (�������� ��������� �� �������� �� ����� ������������� ���� ������ �������; ������� �� ������ nullptr. ����� ����, ������ ������� ������ ������������)
	Cell::Cell(int iSprites) {
		if (iSprites < 0 || iSprites >= Level::get_sprites().size())
			throw std::out_of_range("������ ������ ���� �� ����������. ���������� ��� ���.");
		species = Level::get_sprites()[iSprites];
		creature = nullptr;
	}

	// ���������� ����������� (� ������������� � ��������� ����)
	Cell::Cell(const Cell& copy) noexcept :
		species(copy.species),
		creature(copy.creature),
		itemList() {
		// ��� ��� ���������� ������ ����� ������� ������ ��������� �����, ��� ��� ���������� ���������� ����������� ���� ������ �������������� ���� ������ �������
		for (auto iter = copy.itemList.begin(); iter != copy.itemList.end(); ++iter)
			itemList.push_back((*iter)->clone());
	}


	// ���������� �������� ������������: ����� ��� �� �� ������� ��� ����������� ��������
	Cell& Cell::operator = (const Cell& copy) noexcept {
		if (this != &copy) {
			species = copy.species;
			creature = copy.creature;
			for (auto iter = copy.itemList.begin(); iter != copy.itemList.end(); ++iter)
				itemList.push_back((*iter)->clone());
		}
		return *this;
	}


	/*
		������������ ����������� (�� ������� ������, ��� ������� � �������)
		������������ �������������� ������� � ���, ��� �������� �� ����������, � ����������������� � ������
	*/
	Cell::Cell(Cell&& move) noexcept :
		species(move.species),
		creature(move.creature),
		itemList(move.itemList) {
		move.creature = nullptr;
		move.itemList.clear();
	}


	// ������������ �������� ������������
	Cell& Cell::operator = (Cell&& move) noexcept {
		char tmpSpecies = move.species;
		move.species = species;
		species = tmpSpecies;
		Creature* tmpCreature = move.creature;
		move.creature = creature;
		creature = tmpCreature;
		std::list<Item*> tmpList = move.itemList;
		move.itemList = itemList;
		itemList = tmpList;
		return *this;
	}


	// ��������� (���������������, ��� ��� �������� ����������� �������� �������� �� ����, � ��� ��������� �������� ��� ��� �� ����� ������ ����� �� � ���, ��������� ������ � �������)
	Cell::~Cell() {
		if (!itemList.empty())
			for (auto iter = itemList.begin(); iter != itemList.end(); ++iter)
				delete (*iter);
		itemList.clear();
	}


	/********************************************************/
	/*						�������							*/
	/********************************************************/



	/********************************************************/
	/*						�������							*/
	/********************************************************/

	// �������� ��� ������
	Cell& Cell::set_species(char type) {
		if (Level::get_sprites().find_first_of(type) == std::string::npos)
			throw std::out_of_range("�� ��������� �������� ��� ������ �� ��������������. ����������, ��������/�������� ������� ������ \"�������\"");
		species = type;
		return *this;
	}


	// ���������� ��������� �� �������� (������ exception, ���� ��� ���� ��������� �� ��������)
	Cell& Cell::set_creature(Creature* ptr) {
		auto pos = Level::get_sprites().find_first_of(species);
		if (pos == 1 || pos == 2 || pos == 3)
			throw std::invalid_argument("�� ������ ���� ������ ������ ����������� ��������. �������� ������ ������.");
		if (creature)
			throw std::invalid_argument("�� ������ ������ ��� ���-�� ����. �������� ������ ������.");
		creature = ptr;
		return *this;
	}


	/********************************************************/
	/*					��������� ������					*/
	/********************************************************/


	// ������� � ������� ��������� �� ��������, � ������, ���� ��� ������������� ��� ���� ���������� (�������� �� ��������, � ���������� ��������� ������!!!!); exception, ���� ��������� ����, �� �����, ������ ��������� ������ �� ����
	Creature* Cell::loose_creature() noexcept {
		Creature* tmp = creature;
		creature = nullptr;
		return tmp;
	}


	// ������� �����-�� ������� �� ������ ����� (�������� ������� ���� � ������, �.�. ������ ����� ���������� ������); ���������� exception, ���� ������� � ����� ������� �� ���������� ��� ������ ���� 
	Item* Cell::erase_item(int n) {
		if (n < 1)
			throw std::exception("�������� � ����� ������� ��� ���� �� �����.");
		int size = itemList.size();
		if (!size)
			throw std::exception("����� ��� ������� ���������.");
		if (n > size)
			throw std::exception("�������� � ����� ������� ����� ���. ���������� ��� ���.");
		int i = 1;
		for (auto iter = itemList.begin(); i <= n; iter++) {
			if (i == n) {
				// ��������� ����� ��������� ����
				Item* res = *iter;
				itemList.erase(iter);
				// ���������� ��� ��� ����������� �������������
				return res;
			}
		}
	}


	/*
			int size = cell.itemList.size();
		if (!size)
			os << "����� ��� �����.";
		else
			for (auto iter = cell.itemList.begin(); iter != cell.itemList.end(); ++iter)
				os << "������� #" << size++ << ": " << (*iter) << ";\n";
		return os;
	*/


	// ����� ������
	std::ostream& operator << (std::ostream& os, const Cell& cell) {
		os << cell.get_species();
		return os;
	}


}


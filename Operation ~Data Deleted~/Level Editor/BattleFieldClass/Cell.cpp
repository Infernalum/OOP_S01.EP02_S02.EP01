#include "pch.h"






namespace XCom {



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
		creature(),
		fog(true),
		visible(true) {};


	// �����������, �������� ��� ������� (�������� ��������� �� �������� �� ����� ������������� ���� ������ �������; ������� �� ������ nullptr. ����� ����, ������ ������� ������ ������������)
	Cell::Cell(int iSprites) : fog(false), visible(false) {
		if (iSprites < 0 || iSprites >= (int)Level::get_sprites().size())
			throw std::out_of_range("������ ������ ���� �� ����������. ���������� ��� ���.");
		species = Level::get_sprites()[iSprites];
		creature = nullptr;
	}


	// ���������� ����������� (� ������������� � ��������� ����)
	Cell::Cell(const Cell& copy) noexcept :
		fog(copy.fog),
		visible(copy.visible),
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
			fog = copy.fog;
			visible = copy.visible;
			species = copy.species;
			creature = copy.creature;
			for (auto iter = copy.itemList.begin(); iter != copy.itemList.end(); ++iter)
				itemList.push_back((*iter)->clone());
		}
		return *this;
	}


	// ������������ �������� ������������
	Cell& Cell::operator = (Cell&& move) noexcept {
		std::swap(species, move.species);
		std::swap(fog, move.fog);
		std::swap(visible, move.visible);
		Creature* tmpCreature = move.creature;
		move.creature = creature;
		creature = tmpCreature;
		itemList.swap(move.itemList);
		return *this;
	}


	// ��������� (���������������, ��� ��� �������� ����������� �������� �������� � ������, � ��� ����� ��� ��� �� ����� ������ ����� �� � ���, ��������� ������ � �������)
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


	// �������� ��������� �� ���������� ������� �� ������ ����� (���������� ����� ��������)
	Item* Cell::get_item(int pos) const {
		if (!itemList.size())
			throw std::out_of_range("����� ��� ������� ���������. ���������� ��� ���.");
		if (pos < 1)
			throw std::out_of_range("�������� � ����� ������� ���� �� �����. ���������� ��� ���");
		if (pos > itemList.size())
			throw std::out_of_range("�������� � ����� ������� �� ������ ���. ���������� ��� ���.");
		auto item = itemList.begin();
		for (int i = 1; i < pos; ++i)
			++item;
		return *item;
	}

	// ������� ������ ��������� �� ������
	std::ostream& Cell::show_list(std::ostream& os) const noexcept {
		if (!itemList.size())
			os << "����� ���." << '\n';
		int i = 1;
		for (auto iter = itemList.begin(); iter != itemList.end(); ++iter)
			os << "�" << i++ << ": " << **iter << '\n';
		return os;
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
			throw std::exception("�������� � ����� ������� ���� �� �����. ���������� ��� ���.");
		int size = itemList.size();
		if (!size)
			throw std::exception("����� ��� ������� ���������. ���������� ��� ���.");
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


	// ����� ������
	std::ostream& operator << (std::ostream& os, const Cell& cell) {
		// ���� ��� �������� ��������� (fog true), �� ���� '?' (�����������)
		if (!cell.fog)
			os << '?';
		// ���� ��� ���� ���������, �� � ������ ������ ��������(visible false), �� ������������ ��� ������;
		else if (!cell.visible)
			os << cell.get_species();
		// ���� ��� ���� ���������, � ��������� �� ��� ��� (visible true), �� ������������ ���� ����, ������� �� ���, ���� ��������, ���� ����� ���, ���� ��� ������, ���� �� ����, �� ������� ���
		else {
			if (cell.creature)
				if (cell.creature->get_ID() != CREATUREID_OPERATIVE)
					os << Level::get_markingAliens()[cell.creature->get_ID()];
				else
					os << dynamic_cast<Operative*>(cell.creature)->get_spriteID();
			else if (!cell.empty())
				os << Level::get_sprites()[5];
			else
				os << cell.get_species();
		}
		return os;
	}


	std::ostream& Cell::save(std::ostream& os) const noexcept {
		os << get_species() << ' ' << itemList.size() << '\n';
		for (auto iter = itemList.begin(); iter != itemList.end(); ++iter)
			(*iter)->save(os);
		return os;
	}

}


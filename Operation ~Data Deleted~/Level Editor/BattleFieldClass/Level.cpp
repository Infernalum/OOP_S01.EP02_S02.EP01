#include "pch.h"

#include "Level.h"



namespace Battlefield {

	const std::string Level::sprites = ".#-=&";

	/********************************************************/
	/*					������������						*/
	/********************************************************/


	/*
	���������� �����������
		�� �������� ���� (���� ���������� ���������� ��� ������), ������� ����� ������� �� ������� ��� � ��������������� ���� ������� � �� �������.
		����� �������, ������ ��������� �� ������� �� ����������� ���� ���������� �� ��������� �� ����� �������
	*/
	Level::Level(const Level& copy) noexcept : field(copy.field) {
		for (auto iter = copy.SquadAliens.begin(); iter != copy.SquadAliens.end(); ++iter) {
			Creature* tmp = (*iter)->clone();
			SquadAliens.push_back(tmp);
			field[tmp->y][tmp->x].set_creature(tmp);
		}
		for (auto iter = copy.SquadOperative.begin(); iter != copy.SquadOperative.end(); ++iter) {
			Creature* tmp = (*iter)->clone();
			SquadAliens.push_back(tmp);
			field[tmp->y][tmp->x].set_creature(tmp);
		}
	}


	// ���������� �������� ������������
	Level& Level::operator =(const Level& copy) noexcept {
		if (this != &copy) {
			field = copy.field;
			for (auto iter = copy.SquadAliens.begin(); iter != copy.SquadAliens.end(); ++iter) {
				Creature* tmp = (*iter)->clone();
				SquadAliens.push_back(tmp);
				field[tmp->y][tmp->x].set_creature(tmp);
			}
			for (auto iter = copy.SquadOperative.begin(); iter != copy.SquadOperative.end(); ++iter) {
				Creature* tmp = (*iter)->clone();
				SquadAliens.push_back(tmp);
				field[tmp->y][tmp->x].set_creature(tmp);
			}
		}
		return *this;
	}


	// ������������ �������� ������������
	Level& Level::operator =(Level&& move) noexcept {
		// ??? ����� �� �������� ������ ������ ����������� �����������?
		std::vector<std::vector<Cell>> tmpField = move.field;
		move.field = field;
		field = tmpField;
		std::list<Creature*> tmpList = move.SquadAliens;
		move.SquadAliens = SquadAliens;
		SquadAliens = tmpList;
		tmpList = move.SquadOperative;
		move.SquadOperative = SquadOperative;
		SquadOperative = tmpList;
		return *this;
	}


	/*
	����������
		������� ��������: �������� ������� �� ����� ���, � ����� �������� ����, �. �. ������ ������ �� ������� ��������� ���������, ��� ��� ��� ����
		��� �������,������� ���������: ��������� ��������� (�� ������ � ������������ ��������! � ���� ������ ���� �� �������� �������� �� ������)
	*/
	Level::~Level() {
		for (auto iter = SquadAliens.begin(); iter != SquadAliens.end(); ++iter)
			delete (*iter);
		for (auto iter = SquadOperative.begin(); iter != SquadOperative.end(); ++iter)
			delete (*iter);
		field.clear();
	}

	/********************************************************/
	/*						�������							*/
	/********************************************************/


	// ������� ������ ��������, ���������� �� ������� (��� ����, ����� ����� ����, ��� ��� ����������)
	const std::ostream& Level::print_sptites(std::ostream& os) const noexcept {
		os << " [" << sprites[0] << "] - ���;\n [" << sprites[1] << "] - �����;\n [" << sprites[2] << "] - ������;\n [" << sprites[3] << "] - �����������;\n [" << sprites[4] << "] - ��������� ����� ����������;";
		return os;
	}



	/********************************************************/
	/*						�������							*/
	/********************************************************/


	// ������������� ������� �������� ���� (� ������� �����. ���� �� ������ �� ���������); ��� �������� ������ ����, ������ ���������
	Level& Level::set_proportions(int n, int m) {
		// n - ������, m - ����� (� ���� ��������� �������� ���������� �������)
		if (n < 1 || m < 1)
			throw std::exception("���� � ��������� ����������� ������������ �� �����. ���������� ��� ���.");
		for (auto iter = SquadAliens.begin(); iter != SquadAliens.end(); ++iter)
			delete (*iter);
		for (auto iter = SquadOperative.begin(); iter != SquadOperative.end(); ++iter)
			delete (*iter);
		SquadAliens.clear();
		SquadOperative.clear();
		field.clear();
		field.resize(m);
		for (int i = 0; i < m; ++i)
			field[i].resize(n);
		return *this;
	}


	// ��������� �������� ��� ���������� ������, ���������� ����-���� x � y
	Level& Level::set_cell(int x, int y, int type) {
		if (--x < 0 || x >= (int)field[0].size())
			throw std::exception("���������� x ��� ������ �����. ���������� ��� ���.");
		if (--y < 0 || y >= (int)field.size())
			throw std::exception("���������� y ��� ������ �����. ���������� ��� ���.");
		field[y][x].set_species(sprites[--type]);
		return *this;
	}


	// ��������� �������� � ���� � �� ����
	Level& Level::add_to_level(Creature* cr, int x, int y) {
		if (--x < 0 || --y < 0 || x >= (int)field[0].size() || y >= (int)field.size())
			throw std::exception("���������� ������ ������� �������. �������� ������ ������.");
		// ����������, ��� �� ������ ������ ��� ���� �������� ��� ��� ������ �� ��������� ��������� ���, ������������� � set_creature()
		field[y][x].set_creature(cr);
		if (cr->marking == 'A')
			SquadOperative.push_back(cr);
		else
			SquadAliens.push_back(cr);
		cr->x = x;
		cr->y = y;
		return *this;
	}


	// �������� �������� �� ������ (���������� nullptr, ���� �������� ���, � ����� �������� � ��������� ������)
	Creature* Level::loose_creature(int x, int y) {
		if (--x < 0 || --y < 0 || x >= (int)field[0].size() || y >= (int)field.size())
			throw std::exception("���������� ������ ������� �������. �������� ������ ������.");
		Creature* res = field[x][y].loose_creature();
		return res;
	}


	/********************************************************/
	/*					������ ������						*/
	/********************************************************/

	// ���� �������� ����
	std::istream& operator >> (std::istream& is, Level& field) {
		std::string data;
		int n = field.field[0].size();
		int m = field.field.size();
		for (int i = 0; i < m; ++i) {
			int cur = n;
			is >> data;
			auto pos = data.find_first_not_of(field.sprites);
			if (pos != std::string::npos && (int)pos < cur)
				cur = pos;
			int size = data.size();
			if (size < cur)
				cur = size;
			for (int j = 0; j < cur; ++j)
				field.field[i][j].set_species(data[j]);
			data.clear();
		}
		return is;
	}


	// ����� �������� ����
	std::ostream& operator << (std::ostream& os, const Level& field) {
		int n = field.field[0].size();
		int  m = field.field.size();
		// ������� ���������� �� X
		os << ' ';
		for (int i = 1; i <= n; ++i) {
			int c = i, first;
			while (c > 0) {
				first = c % 10;
				c /= 10;
			}
			os << first;
		}
		os << '\n';
		for (int i = 0; i < m; ++i) {
			int c = i + 1, first;
			while (c > 0) {
				first = c % 10;
				c /= 10;
			}
			os << first;
			for (int j = 0; j < n; ++j)
				if (field.field[i][j].get_creature())
					if (field.field[i][j].get_creature()->name() == 0)
						os << field.field[i][j].get_creature()->name();
					else
						os << field.field[i][j].get_creature()->name();
				else
					os << field.field[i][j];
			os << '\n';
		}
		return os;
	}


}

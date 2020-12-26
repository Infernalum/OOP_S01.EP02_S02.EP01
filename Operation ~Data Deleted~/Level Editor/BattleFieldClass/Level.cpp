#include "pch.h"

#include "Level.h"



namespace XCom {

	const std::string Level::sprites = ".#-=&!";

	const std::string Level::markingAliens = "pcm";

	/********************************************************/
	/*					������������						*/
	/********************************************************/


	/*
	���������� �����������
		�� �������� ���� (���� ���������� ���������� ��� ������), ������� ����� ������� �� ������� ��� � ��������������� ���� ������� � �� �������.
		����� �������, ������ ��������� �� ������� �� ����������� ���� ���������� �� ��������� �� ����� �������
	*/
	Level::Level(const Level& copy) noexcept : field(copy.field), ammo(copy.ammo) {
		for (auto iter = copy.squadAliens.begin(); iter != copy.squadAliens.end(); ++iter) {
			Creature* tmp = (*iter)->clone();
			squadAliens.push_back(tmp);
			field[tmp->get_y()][tmp->get_x()].set_creature(tmp);
		}
		for (auto iter = copy.squadOperative.begin(); iter != copy.squadOperative.end(); ++iter) {
			Creature* tmp = (*iter)->clone();
			squadAliens.push_back(tmp);
			field[tmp->get_y()][tmp->get_x()].set_creature(tmp);
		}
	}


	// ���������� �������� ������������
	Level& Level::operator =(const Level& copy) noexcept {
		if (this != &copy) {
			field = copy.field;
			ammo = copy.ammo;
			for (auto iter = copy.squadAliens.begin(); iter != copy.squadAliens.end(); ++iter) {
				Creature* tmp = (*iter)->clone();
				squadAliens.push_back(tmp);
				field[tmp->get_y()][tmp->get_x()].set_creature(tmp);
			}
			for (auto iter = copy.squadOperative.begin(); iter != copy.squadOperative.end(); ++iter) {
				Creature* tmp = (*iter)->clone();
				squadAliens.push_back(tmp);
				field[tmp->get_y()][tmp->get_x()].set_creature(tmp);
			}
		}
		return *this;
	}


	// ������������ �������� ������������
	Level& Level::operator =(Level&& move) noexcept {
		field.swap(move.field);
		squadAliens.swap(move.squadAliens);
		squadOperative.swap(move.squadOperative);
		return *this;
	}


	/*
	����������
		������� ��������: �������� ������� �� ����� ���, � ����� �������� ����, �. �. ������ ������ �� ������� ��������� ���������, ��� ��� ��� ����
		��� �������,������� ���������: ��������� ��������� (�� ������ � ������������ ��������! � ���� ������ ���� �� �������� �������� �� ������)
	*/
	Level::~Level() {
		for (auto iter = squadAliens.begin(); iter != squadAliens.end(); ++iter)
			delete (*iter);
		for (auto iter = squadOperative.begin(); iter != squadOperative.end(); ++iter)
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
		for (auto iter = squadAliens.begin(); iter != squadAliens.end(); ++iter)
			delete (*iter);
		for (auto iter = squadOperative.begin(); iter != squadOperative.end(); ++iter)
			delete (*iter);
		squadAliens.clear();
		squadOperative.clear();
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
		if (cr->get_ID() == CREATUREID_OPERATIVE)
			squadOperative.push_back(cr);
		else
			squadAliens.push_back(cr);
		cr->set_x(x);
		cr->set_y(y);
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


	/*
		������� ����������� (������) ��������: ��� ������� ������ �������� ���� ������� �������� ��� � ����.
	(��������! ��� ���������� ������ ������ �������� ���� ���������� �������� �������������� ����!!!)
	*/
	Level& Level::destruction(Creature*& target) {

		return *this;
	}



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


	std::ostream& Level::save(std::ostream& os) {
		os << squadOperative.size() << '\n';
		for (auto iter = squadOperative.begin(); iter != squadOperative.end(); iter++)
			(*iter)->save(os);
		os << squadAliens.size() << '\n';
		for (auto iter = squadAliens.begin(); iter != squadAliens.end(); iter++)
			(*iter)->save(os);
		int n = field[0].size();
		int  m = field.size();
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				field[j][i].save(os);
			}
		return os;
	}


	// ����� �������� ����
	std::ostream& operator << (std::ostream& os, const Level& field) {
		int n = field.field[0].size();
		int  m = field.field.size();
		// ������� ���������� �� X
		os << ' ' << ' ';
		for (int i = 1; i <= n; ++i) {
			int c = i, first;
			while (c > 0) {
				first = c % 10;
				c /= 10;
			}
			os << first;
		}
		os << '\n' << ' ' << ' ';
		for (int i = 1; i <= n; ++i)
			os << '-';
		os << '\n';
		for (int i = 0; i < m; ++i) {
			int c = i + 1, first;
			while (c > 0) {
				first = c % 10;
				c /= 10;
			}
			os << first << '|';
			for (int j = 0; j < n; ++j)
				os << field.field[i][j];
			os << '\n';
		}

		os << " ������� �������������:\n";
		if (!field.squadOperative.size())
			std::cout << "������� �����;\n";
		else
			for (auto iter = field.squadOperative.begin(); iter != field.squadOperative.end(); iter++)
				std::cout << **iter << '\n';

		os << " ������� ����������:\n";
		if (!field.squadAliens.size())
			std::cout << "������� �����;\n";
		else
			for (auto iter = field.squadAliens.begin(); iter != field.squadAliens.end(); iter++)
				std::cout << **iter << '\n';
		os << "\n �������� �� �����:\n";
		bool check = false;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				if (!field.field[j][i].empty()) {
					os << "������ (" << i << "\\" << j << "):\n";
					field.field[j][i].show_list(os);
					check = true;
				}
			}
		if (!check)
			os << "��� ���������.\n";

		os << '\n';
		return os;
	}


}


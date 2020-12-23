#include "pch.h"

#include "Chryssalid.h"

namespace XCom {


	Chryssalid& Chryssalid::set_damage(int d) {
		if (d < 0)
			throw std::invalid_argument("����� ���������� �� ����� ���� �������������. ����������, ������� ������������� �����.");
		damage = d;
		return *this;
	}


	Chryssalid& Chryssalid::set_scatter(int scat) {
		if (scat < 0)
			throw std::invalid_argument("������� ����� ���������� �� ����� ���� �������������. ����������, ������� ������������� �����.");
		scatter = scat;
		return *this;
	}




	/********************************************************/
	/*					��������� ������					*/
	/********************************************************/

	int Chryssalid::get_damage(Creature* target) {
		int delta_x = abs(change_coords().first - target->change_coords().first);
		int delta_y = abs(change_coords().second - target->change_coords().second);
		int distance = delta_x + delta_y;
		if (distance <= 2) {
			srand(time(0));
			// ���� ���������
			double chance = 95 * (double)get_accurany() / 100 * (1 - (double)target->get_evasion() * 0.5);
			double range = 0 + rand() % 100;
			if (range > chance)
				throw std::invalid_argument("��������� �������������! �������.");
			int res = (damage - scatter) + rand() % (damage + scatter);
			if (res < 0)
				res = 0;
			target->set_HP(target->get_HP() - res);
			return res;
		}
		else {
			throw std::invalid_argument("���� ��������� ������� ������. ���������� ��� ���.");
		}
	}


	std::ostream& Chryssalid::print(std::ostream& os) const {
		os << "��������: ���������; ";
		Creature::print(os);
		os << " ���� � ������� ���: " << damage << ';';
		return os;
	}


	std::ostream& Chryssalid::save(std::ostream& os) const noexcept {
		Creature::save(os);
		os << damage << ' ' << scatter << '\n';
		return os;
	}

	std::istream& Chryssalid::load(std::istream& is) noexcept {
		Creature::load(is);
		is.ignore();
		int _int;
		is >> _int;
		set_damage(_int);
		is.ignore();
		is >> _int;
		set_scatter(_int);
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return is;
	}

}

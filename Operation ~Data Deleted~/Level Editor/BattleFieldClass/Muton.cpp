#include "pch.h"


namespace XCom {


	Weapon* Muton::change_weapon(Weapon* ptr) noexcept {
		Weapon* _old = hand;
		hand = ptr;
		return _old;
	}


	std::ostream& Muton::print(std::ostream& os) const noexcept {
		os << "��������: �������� ��������; ";
		Creature::print(os);
		os << " ������ � ����: ";
		if (hand)
			os << *hand;
		else
			os << "���;";
		os << '\n';
		return os;
	}


	std::ostream& Muton::save(std::ostream& os) const noexcept {
		Creature::save(os);
		if (hand) {
			os << 1 << ' ';
			hand->save(os);
		}
		else
			os << 0 << ' ';
		return os;
	}



	std::istream& Muton::load(std::istream& is) noexcept {
		Creature::load(is);
		int state;
		is.ignore() >> state;
		if (state) {
			Weapon* wp = new Weapon;
			// ������� ������������� ��������
			is.ignore() >> state;
			is.ignore();
			wp->load(is);
			hand = wp;
		}
		else
			// ���������� ��� ���������� ������, ���, �� ������
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return is;
	}


}

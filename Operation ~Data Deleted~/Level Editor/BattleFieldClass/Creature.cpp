#include "pch.h"


namespace XCom {

	/********************************************************/
	/*					 ������������						*/
	/********************************************************/



	/********************************************************/
	/*						�������							*/
	/********************************************************/



	/********************************************************/
	/*						�������							*/
	/********************************************************/


	void Creature::set_x(int x0) {
		if (x0 < 0)
			throw std::invalid_argument("����������� x �� ����� ���� �������������. ���������� ��� ���.");
		coords.first = x0;
	}


	void Creature::set_y(int y0) {
		if (y0 < 0)
			throw std::invalid_argument("����������� y �� ����� ���� �������������. ���������� ��� ���.");
		coords.second = y0;
	}


	void Creature::set_evasion(int ev) {
		if (ev < 0 || ev > 100)
			throw std::invalid_argument("�������� ��������� ������ ���� ������ � �������� �� 0 �� 100%. ���������� ��� ���.");
		evasion = ev;
	}


	void Creature::set_accuracy(int acc) {
		if (acc < 0 || acc > 100)
			throw std::invalid_argument("�������� �������� ������ ���� ����� � �������� �� 0 �� 100%. ���������� ��� ���.");
		accuracy = acc;
	}


	void Creature::set_HP(int hp) {
		if (hp < 1)
			throw std::invalid_argument("������� �������� �������� �� ����� ���� �������������. ���������� ��� ���.");
		if (hp > maxHP)
			HP = maxHP;
		else
			HP = hp;
	}


	void Creature::set_maxHP(int mh) {
		if (mh < 1)
			throw std::invalid_argument("������������ �������� �������� �� ����� ���� �������������. ���������� ��� ���.");
		maxHP = mh;
		if (HP > maxHP)
			HP = maxHP;
	}


	void Creature::set_TP(int tp) {
		if (tp < 0)
			throw std::invalid_argument("������� ���-�� ����� ������� �� ����� ���� �������������. ���������� ��� ���.");
		if (tp > maxTP)
			TP = maxTP;
		else
			TP = tp;
	}


	void Creature::set_maxTP(int mtp) {
		if (mtp < 0)
			throw std::invalid_argument("������������ �������� ����� ������� �������� �� ����� ���� �������������. ���������� ��� ���.");
		maxTP = mtp;
		if (TP > maxTP)
			TP = maxTP;
	}


	void Creature::set_sight(int s) {
		if (s < 0)
			throw std::invalid_argument("������ ������ �������� �� ����� ���� �������������. ���������� ��� ���.");
		sight = s;
	}


	/********************************************************/
	/*					��������� ������					*/
	/********************************************************/



	std::ostream& Creature::print(std::ostream& os) const noexcept {
		os << "����������: ";
		if (coords.first < 0 || coords.second < 0)
			os << "undefined";
		else
			os << coords.first << '\\' << coords.second;
		return os << "; ������ ������: " << sight << "; HP: " << HP << '\\' << maxHP << "; TP: " << TP << '\\' << maxTP << ";\n";
	}

	std::ostream& Creature::save(std::ostream& os) const noexcept {
		os << ID << ' ' << coords.first << ' ' << coords.second << ' ' << HP << ' ' << maxHP << ' ' << evasion << ' ' << accuracy << ' ' << TP << ' ' << maxTP << ' ' << sight << ' ';
		return os;
	}



	std::istream& Creature::load(std::istream& is) noexcept {
		is >> coords.first;
		is.ignore() >> coords.second;
		is.ignore() >> HP;
		is.ignore() >> maxHP;
		is.ignore() >> evasion;
		is.ignore() >> accuracy;
		is.ignore() >> TP;
		is.ignore() >> maxTP;
		is.ignore() >> sight;
		return is;
	}


}

#include "pch.h"
#include "Creature.h"


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


	Creature& Creature::set_x(int x0) {
		if (x0 < 0)
			throw std::invalid_argument("����������� x �� ����� ���� �������������. ���������� ��� ���.");
		x = x0;
		return *this;
	}


	Creature& Creature::set_y(int y0) {
		if (y0 < 0)
			throw std::invalid_argument("����������� y �� ����� ���� �������������. ���������� ��� ���.");
		y = y0;
		return *this;
	}


	Creature& Creature::set_evasion(int ev) {
		if (ev < 0 || ev > 100)
			throw std::invalid_argument("�������� ��������� ������ ���� ������ � �������� �� 0 �� 100%. ���������� ��� ���.");
		evasion = ev;
		return *this;
	}


	Creature& Creature::set_accuracy(int acc) {
		if (acc < 0 || acc > 100)
			throw std::invalid_argument("�������� �������� ������ ���� ����� � �������� �� 0 �� 100%. ���������� ��� ���.");
		accuracy = acc;
		return *this;
	}


	Creature& Creature::set_HP(int hp) {
		if (hp < 1)
			throw std::invalid_argument("������� �������� �������� ������ ���� �������������. ���������� ��� ���.");
		if (hp > maxHP)
			HP = maxHP;
		else
			HP = hp;
		return *this;
	}


	Creature& Creature::set_maxHP(int mh) {
		if (mh < 1)
			throw std::invalid_argument("������������ �������� �������� ������ ���� �������������. ���������� ��� ���.");
		maxHP = mh;
		return *this;
	}


	Creature& Creature::set_TP(int tp) {
		if (tp < 1)
			throw std::invalid_argument("������� ���-�� ����� ������� ������ ���� �������������. ���������� ��� ���.");
		if (tp > maxTP)
			TP = maxTP;
		else
			TP = tp;
		return *this;
	}


	Creature& Creature::set_maxTP(int mtp) {
		if (mtp < 1)
			throw std::invalid_argument("������������ �������� ����� ������� �������� ������ ���� �������������. ���������� ��� ���.");
		maxTP = mtp;
		return *this;
	}


	Creature& Creature::set_sight(int s) {
		if (s < 1)
			throw std::invalid_argument("������ ������ �������� ������ ���� �������������. ���������� ��� ���.");
		sight = s;
		return *this;
	}

	/********************************************************/
	/*					��������� ������					*/
	/********************************************************/


	std::ostream& Creature::print(std::ostream& os) const {
		os << "����������: ";
		if (x < 0 || y < 0)
			os << "undefined";
		else
			os << x << '\\' << y;
		return os << "; ������ ������: " << sight << "; HP: " << HP << '\\' << maxHP << "; ���� �������: " << TP << '\\' << maxTP << ";";
	}


}

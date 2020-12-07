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
		coords.first = x0;
		return *this;
	}


	Creature& Creature::set_y(int y0) {
		if (y0 < 0)
			throw std::invalid_argument("����������� y �� ����� ���� �������������. ���������� ��� ���.");
		coords.second = y0;
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
			throw std::invalid_argument("������� �������� �������� �� ����� ���� �������������. ���������� ��� ���.");
		if (hp > maxHP)
			HP = maxHP;
		else
			HP = hp;
		return *this;
	}


	Creature& Creature::set_maxHP(int mh) {
		if (mh < 1)
			throw std::invalid_argument("������������ �������� �������� �� ����� ���� �������������. ���������� ��� ���.");
		maxHP = mh;
		if (HP > maxHP)
			HP = maxHP;
		return *this;
	}


	Creature& Creature::set_TP(int tp) {
		if (tp < 0)
			throw std::invalid_argument("������� ���-�� ����� ������� �� ����� ���� �������������. ���������� ��� ���.");
		if (tp > maxTP)
			TP = maxTP;
		else
			TP = tp;
		return *this;
	}


	Creature& Creature::set_maxTP(int mtp) {
		if (mtp < 0)
			throw std::invalid_argument("������������ �������� ����� ������� �������� �� ����� ���� �������������. ���������� ��� ���.");
		maxTP = mtp;
		if (TP > maxTP)
			TP = maxTP;
		return *this;
	}


	Creature& Creature::set_sight(int s) {
		if (s < 0)
			throw std::invalid_argument("������ ������ �������� �� ����� ���� �������������. ���������� ��� ���.");
		sight = s;
		return *this;
	}

	/********************************************************/
	/*					��������� ������					*/
	/********************************************************/


	std::ostream& Creature::print(std::ostream& os) const {
		os << "����������: ";
		if (coords.first < 0 || coords.second < 0)
			os << "undefined";
		else
			os << coords.first << '\\' << coords.second;
		return os << "; ������ ������: " << sight << "; HP: " << HP << '\\' << maxHP << "; ���� �������: " << TP << '\\' << maxTP << ";";
	}


}

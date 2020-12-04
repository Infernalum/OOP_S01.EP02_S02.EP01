#include "pch.h"

#include "Chryssalid.h"

namespace Battlefield {

	const char Chryssalid::marking = 'c';



	Chryssalid& Chryssalid::set_damage(int d) {
		if (d < 0)
			throw std::invalid_argument("����� ���������� �� ����� ���� �������������. ����������, ������� ������������� �����.");
		damage = d;
		return *this;
	}




	/********************************************************/
	/*					��������� ������					*/
	/********************************************************/

	std::ostream& Chryssalid::print(std::ostream& os) const {
		os << "��������: ���������; ";
		Creature::print(os);
		os << " ���� � ������� ���: " << damage << ';';
		return os;
	}




}

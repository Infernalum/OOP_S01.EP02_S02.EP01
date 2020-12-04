#include "pch.h"

#include "Chryssalid.h"

namespace Battlefield {

	const char Chryssalid::marking = 'c';



	Chryssalid& Chryssalid::set_damage(int d) {
		if (d < 0)
			throw std::invalid_argument("Дамаг криссалида не может быть отрицательным. Пожалуйста, введите положительное число.");
		damage = d;
		return *this;
	}




	/********************************************************/
	/*					Остальные методы					*/
	/********************************************************/

	std::ostream& Chryssalid::print(std::ostream& os) const {
		os << "Существо: Криссалид; ";
		Creature::print(os);
		os << " урон в ближнем бою: " << damage << ';';
		return os;
	}




}

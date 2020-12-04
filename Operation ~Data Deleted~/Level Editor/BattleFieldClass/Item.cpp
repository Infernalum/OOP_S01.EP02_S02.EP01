#include "pch.h"
#include "Item.h"

namespace Battlefield {



	/********************************************************/
	/*						Сеттеры							*/
	/********************************************************/

	Item& Item::set_weight(int w) {
		if (w < 1)
			throw std::invalid_argument("Вес предмета должен быть положительным. Попробуйте еще раз.");
		weight = w;
		return *this;
	}

	Item& Item::set_usedPoint(int uP) {
		if (uP < 1)
			throw std::invalid_argument("Кол-во расходных очков времени должно быть положительным. Попробуйте еще раз.");
		usedPoint = uP;
		return *this;
	}


}

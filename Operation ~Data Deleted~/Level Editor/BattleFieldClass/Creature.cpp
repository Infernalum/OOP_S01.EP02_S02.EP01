#include "pch.h"
#include "Creature.h"


namespace XCom {

	/********************************************************/
	/*					 Конструкторы						*/
	/********************************************************/



	/********************************************************/
	/*						Геттеры							*/
	/********************************************************/



	/********************************************************/
	/*						Сеттеры							*/
	/********************************************************/


	Creature& Creature::set_x(int x0) {
		if (x0 < 0)
			throw std::invalid_argument("Коородината x не может быть отрицательной. Попробуйте еще раз.");
		x = x0;
		return *this;
	}


	Creature& Creature::set_y(int y0) {
		if (y0 < 0)
			throw std::invalid_argument("Коородината y не может быть отрицательной. Попробуйте еще раз.");
		y = y0;
		return *this;
	}


	Creature& Creature::set_evasion(int ev) {
		if (ev < 0 || ev > 100)
			throw std::invalid_argument("Параметр уклонения должен быть указан в пределах от 0 до 100%. Попробуйте еще раз.");
		evasion = ev;
		return *this;
	}


	Creature& Creature::set_accuracy(int acc) {
		if (acc < 0 || acc > 100)
			throw std::invalid_argument("Параметр точности должен быть задан в пределах от 0 до 100%. Попробуйте еще раз.");
		accuracy = acc;
		return *this;
	}


	Creature& Creature::set_HP(int hp) {
		if (hp < 1)
			throw std::invalid_argument("Текущее здоровье существа должно быть положительным. Попробуйте еще раз.");
		if (hp > maxHP)
			HP = maxHP;
		else
			HP = hp;
		return *this;
	}


	Creature& Creature::set_maxHP(int mh) {
		if (mh < 1)
			throw std::invalid_argument("Максимальное здоровье существа должно быть положительным. Попробуйте еще раз.");
		maxHP = mh;
		return *this;
	}


	Creature& Creature::set_TP(int tp) {
		if (tp < 1)
			throw std::invalid_argument("Текущее кол-во очков времени должно быть положительным. Попробуйте еще раз.");
		if (tp > maxTP)
			TP = maxTP;
		else
			TP = tp;
		return *this;
	}


	Creature& Creature::set_maxTP(int mtp) {
		if (mtp < 1)
			throw std::invalid_argument("Максимальное значение очков времени существа должно быть положительным. Попробуйте еще раз.");
		maxTP = mtp;
		return *this;
	}


	Creature& Creature::set_sight(int s) {
		if (s < 1)
			throw std::invalid_argument("Радиус обзора существа должен быть положительным. Попробуйте еще раз.");
		sight = s;
		return *this;
	}

	/********************************************************/
	/*					Остальные методы					*/
	/********************************************************/


	std::ostream& Creature::print(std::ostream& os) const {
		os << "Координаты: ";
		if (x < 0 || y < 0)
			os << "undefined";
		else
			os << x << '\\' << y;
		return os << "; радиус обзора: " << sight << "; HP: " << HP << '\\' << maxHP << "; Очки времени: " << TP << '\\' << maxTP << ";";
	}


}

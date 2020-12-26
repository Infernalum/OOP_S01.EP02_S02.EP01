#include "pch.h"

namespace XCom {

	/********************************************************/
	/*					 Конструкторы						*/
	/********************************************************/


	// Единственный конструктор
	Item::Item(int id, int uP) : ID(id), weight(0) {
		if (uP < 1)
			throw std::invalid_argument("Количество затрачиваемых TP должно быть положительным. Попробуйте еще раз.");
		usedPoint = uP;
	}



	/********************************************************/
	/*						Сеттеры							*/
	/********************************************************/


	void Item::set_weight(double val) {
		if (val < 0)
			throw std::invalid_argument("Вес предмета не может быть отрицательным. Попробуйте еще раз.");
		weight = val;
	}


	void Item::set_usedPoint(int uP) {
		if (uP < 1)
			throw std::invalid_argument("Кол-во расходных очков времени должно быть положительным. Попробуйте еще раз.");
		usedPoint = uP;
	}


	std::ostream& Item::print(std::ostream& os) const noexcept {
		os << weight << " кг; TP: " << usedPoint << "; ";
		return os;
	}


	std::ostream& Item::save(std::ostream& os) const noexcept {
		os << ID << ' ' << usedPoint << ' ';
		return os;
	}


	std::istream& Item::load(std::istream& is) noexcept {
		int uP;
		is >> uP;
		usedPoint = uP;
		is.ignore();
		return is;
	}

	const std::pair<std::string, double> Ammo::_default = { "5,45*39 мм", 0.01 };


	Ammo::Ammo(const std::pair<std::string, double>& pair) {
		type = pair;
	}


	Ammo::Ammo(const std::string& name, double weight) {
		if (weight <= 0)
			throw std::invalid_argument("Вес патрона должен быть положительным. Попробуйте еще раз.");
		type.first = name;
		type.second = weight;
	}


	Ammo& Ammo::set_weigth(double weight) {
		if (weight <= 0)
			throw std::invalid_argument("Вес патрона должен быть положительным. Попробуйте еще раз.");
		weight = weight;
		return *this;
	}


	std::ostream& Ammo::save(std::ostream& os) const noexcept {
		os << type.second << ' ' << type.first << '\n';
		return os;
	}


	std::ostream& operator <<(std::ostream& os, const Ammo& ammo) noexcept {
		os << "тип патрона: " << ammo.type.first << " (" << ammo.type.second << " кг); ";
		return os;
	}


	std::istream& Ammo::load(std::istream& is) noexcept {
		is >> type.second;
		is.ignore();
		std::getline(is, type.first);
		return is;
	}

}

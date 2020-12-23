#include "pch.h"

namespace XCom {

	/********************************************************/
	/*					 Конструкторы						*/
	/********************************************************/

	// Конструктор, создающий полную аптечку с 3-мя использованиями, восстанавливающую 2 HP и тратящую на использование 2 TP
	FirstAidKit::FirstAidKit(int up, int hp, double wof, int maxqty) : Item(up) {
		if (wof <= 0)
			throw std::invalid_argument("Вес заряда аптечки должен быть положительным. Попробуйте еще раз.");
		if (maxqty < 0)
			throw std::invalid_argument("Аптечка не может иметь отрицательный запас прочности. Попробуйте еще раз.");
		marking = 'F';
		weightOfOne = wof;
		maxQty = maxqty;
		qty = maxQty;
		set_weight(0);
	}

	/********************************************************/
	/*						Геттеры							*/
	/********************************************************/

	// Проверка аптечки на пустоту
	bool FirstAidKit::empty() const noexcept {
		if (!qty)
			return true;
		else
			return false;
	}


	/********************************************************/
	/*						Сеттеры							*/
	/********************************************************/


	FirstAidKit& FirstAidKit::set_qty(int q) {
		if (q < 0)
			throw std::invalid_argument("Текущая прочность аптечки должен быть положительным. Попробуйте еще раз.");
		if (q > maxQty)
			qty = maxQty;
		qty = q;
		set_weight(0);
		return *this;
	}


	FirstAidKit& FirstAidKit::set_max_qty(int mq) {
		if (mq < 0)
			throw std::invalid_argument("Прочность аптечки не может быть отрицательной. Попробуйте еще раз.");
		maxQty = mq;
		if (qty > maxQty) {
			qty = maxQty;
			set_weight(0);
		}
		return *this;
	}


	FirstAidKit& FirstAidKit::set_weight_of_one(double woo) {
		if (woo <= 0)
			throw std::invalid_argument("Вес заряда аптечки должен быть положительным. Попробуйте еще раз.");
		weightOfOne = woo;
		set_weight(0);
		return *this;
	}

	FirstAidKit& FirstAidKit::set_rec(int hp) {
		if (hp < 0)
			throw std::invalid_argument("Аптечка не может восстанавливать отрицательное кол-во здоровья. Попробуйте еще раз.");
		rec = hp;
		return *this;
	}

	/********************************************************/
	/*					Остальные методы					*/
	/********************************************************/


	int FirstAidKit::using_item(int fictitious) {
		int res;
		if (!qty) {
			res = 0;
		}
		else {
			res = rec;
			--qty;
			// Пересчитываем вес
			set_weight(0);
		}
		return res;
	}


	std::ostream& FirstAidKit::print(std::ostream& os) const noexcept {
		os << "Аптечка; запас: " << qty << '\\' << maxQty << "Кол-во восстанавливаемых ОЖ:" << rec << "; Вес: " << get_weight() << "; ";
		Item::print(os);
		return os;
	}


	std::ostream& FirstAidKit::save(std::ostream& os) const noexcept {
		os << get_uP() << ' ' << qty << ' ' << maxQty << ' ' << rec << ' ' << weightOfOne << '\n';
		return os;
	}

	std::istream& FirstAidKit::load(std::istream& is) noexcept {
		int _int;
		double _double;
		is >> _int;
		set_usedPoint(_int);
		is.ignore();
		is >> _int;
		set_qty(_int);
		is.ignore();
		is >> _int;
		set_max_qty(_int);
		is.ignore();
		is >> rec;
		set_rec(_int);
		is.ignore();
		is >> _double;
		set_weight_of_one(_double);
		set_weight(0);
		// Игнорируем всю оставшуюся строку, так, на всякий
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return is;
	}


}



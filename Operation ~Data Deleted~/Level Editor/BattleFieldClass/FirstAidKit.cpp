#include "pch.h"

namespace XCom {

	/********************************************************/
	/*					 Конструкторы						*/
	/********************************************************/

	// Конструктор, создающий полную аптечку с 3-мя использованиями, восстанавливающую 2 HP и тратящую на использование 2 TP
	FirstAidKit::FirstAidKit(int up, int hp, double wof, int maxqty) : Item(ITEMID_FIRSTAIDKIT, up) {
		if (wof <= 0)
			throw std::invalid_argument("Вес заряда аптечки должен быть положительным. Попробуйте еще раз.");
		if (maxqty < 0)
			throw std::invalid_argument("Аптечка не может иметь отрицательный запас прочности. Попробуйте еще раз.");
		rec = hp;
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


	FirstAidKit& FirstAidKit::set_maxQty(int mq) {
		if (mq < 0)
			throw std::invalid_argument("Прочность аптечки не может быть отрицательной. Попробуйте еще раз.");
		maxQty = mq;
		if (qty > maxQty) {
			qty = maxQty;
			set_weight(0);
		}
		return *this;
	}


	FirstAidKit& FirstAidKit::set_weightOfOne(double woo) {
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
		os << "Аптечка (" << qty << '\\' << maxQty << "); восстанавливает HP: " << rec << "; ";
		Item::print(os);
		return os;
	}


	std::ostream& FirstAidKit::save(std::ostream& os) const noexcept {
		Item::save(os) << qty << ' ' << maxQty << ' ' << rec << ' ' << weightOfOne << '\n';
		return os;
	}

	std::istream& FirstAidKit::load(std::istream& is) noexcept {
		Item::load(is) >> qty;
		is.ignore() >> maxQty;
		is.ignore() >> rec;
		is.ignore() >> weightOfOne;
		set_weight(0);
		// Игнорируем всю оставшуюся строку, так, на всякий
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return is;
	}


}



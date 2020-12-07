#include "pch.h"

namespace XCom {

	/********************************************************/
	/*					 Конструкторы						*/
	/********************************************************/

	// Конструктор, создающий ящик с 40 патронами и тратящий 2 TP на перезарядку
	AmmoBox::AmmoBox(int up, double wof, int maxqty) : Item(up) {
		if (wof <= 0)
			throw std::invalid_argument("Вес патрона должен быть положительным. Попробуйте еще раз.");
		if (maxqty < 0)
			throw std::invalid_argument("Ящик не может иметь отрицательный боезапас. Попробуйте еще раз.");
		weightOfOne = wof;
		maxQty = maxqty;
		qty = maxqty;
		set_weight();
	}



	/********************************************************/
	/*						Геттеры							*/
	/********************************************************/

	// Проверка ящика на пустоту
	bool AmmoBox::empty() {
		if (!qty)
			return true;
		else
			return false;
	}


	/********************************************************/
	/*						Сеттеры							*/
	/********************************************************/


	AmmoBox& AmmoBox::set_qty(int q) {
		if (q < 0)
			throw std::invalid_argument("Кол-во патронов в ящике должно быть положительным. Попробуйте еще ра.");
		if (q > maxQty)
			qty = maxQty;
		qty = q;
		set_weight();
		return *this;
	}


	AmmoBox& AmmoBox::set_max_qty(int mq) {
		if (mq < 0)
			throw std::invalid_argument("Максимальное кол-во патронов не может быть отрицательным. Попробуйте еще раз.");
		maxQty = mq;
		if (qty > maxQty) {
			qty = maxQty;
			set_weight();
		}
		return *this;
	}


	AmmoBox& AmmoBox::set_weight_of_one(double woo) {
		if (woo <= 0)
			throw std::invalid_argument("Вес одного патрона должен быть положительным. Попробуйте еще раз.");
		weightOfOne = woo;
		set_weight();
		return *this;
	}


	// Пересчет веса ящика с патронами
	const AmmoBox& AmmoBox::set_weight() {
		weight = weightOfOne * qty;
		return *this;
	}

	/********************************************************/
	/*					Остальные методы					*/
	/********************************************************/


	// Использование предмета: вытащить count патронов из ящика. Если в ящике меньше count патронов, то вытаскивается, сколько есть.
	int AmmoBox::using_item(int count) {
		if (count < 0)
			throw std::invalid_argument("Кол-во патронов, которые вы хотите вытащить, должно быть положительным. Попробуйте еще раз.");
		int res;
		if (qty < count) {
			res = qty;
			qty = 0;
		}
		else {
			res = count;
			qty -= count;
		}
		// Пересчитываем вес
		set_weight();
		return res;
	}


	std::ostream& AmmoBox::print(std::ostream& os) const {
		os << "Предмет: аптечка; патроны: " << qty << '\\' << maxQty << "; Вес: " << weight << "; ";
		Item::print(os);
		return os;
	}

}

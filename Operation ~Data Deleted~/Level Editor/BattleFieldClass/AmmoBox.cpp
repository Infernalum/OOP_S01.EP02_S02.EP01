#include "pch.h"

namespace XCom {

	/********************************************************/
	/*					 Конструкторы						*/
	/********************************************************/


	AmmoBox::AmmoBox(const Ammo& type, int up, int maxqty) : Item(ITEMID_AMMOBOX, up) {
		if (maxqty < 0)
			throw std::invalid_argument("Ящик не может иметь отрицательный боезапас. Попробуйте еще раз.");
		ammo = type;
		maxQty = maxqty;
		qty = maxqty;
		set_weight(0);
	}



	/********************************************************/
	/*						Геттеры							*/
	/********************************************************/

	// Проверка ящика на пустоту
	bool AmmoBox::empty() const noexcept {
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
		set_weight(0);
		return *this;
	}


	AmmoBox& AmmoBox::set_maxQty(int mq) {
		if (mq < 0)
			throw std::invalid_argument("Максимальное кол-во патронов не может быть отрицательным. Попробуйте еще раз.");
		maxQty = mq;
		if (qty > maxQty) {
			qty = maxQty;
			set_weight(0);
		}
		return *this;
	}

	/********************************************************/
	/*					Остальные методы					*/
	/********************************************************/


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
		set_weight(0);
		return res;
	}


	std::ostream& AmmoBox::print(std::ostream& os) const noexcept {
		os << "Ящик с патронами (" << qty << '\\' << maxQty << "); ";
		Item::print(os);
		os << ammo;
		return os;
	}


	std::ostream& AmmoBox::save(std::ostream& os) const noexcept {
		Item::save(os) << qty << ' ' << maxQty << '\n';
		ammo.save(os);
		return os;
	}


	std::istream& AmmoBox::load(std::istream& is) noexcept {
		Item::load(is) >> qty;
		is.ignore() >> maxQty;
		is.ignore() >> ammo;
		return is;
	}
}

#include "pch.h"

namespace XCom {

	/********************************************************/
	/*					 Конструкторы						*/
	/********************************************************/

	// Конструктор, создающий ящик с 40 патронами и тратящий 2 TP на перезарядку
	AmmoBox::AmmoBox(int up, int maxqty,const Ammo& ammo) : Item(up) {
		if (maxqty < 0)
			throw std::invalid_argument("Ящик не может иметь отрицательный боезапас. Попробуйте еще раз.");
		marking = 'A';
		type = ammo;
		maxQty = maxqty;
		qty = maxqty;
		set_weight(0);
	}



	/********************************************************/
	/*						Геттеры							*/
	/********************************************************/

	// Проверка ящика на пустоту
	bool AmmoBox::empty() const noexcept{
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


	AmmoBox& AmmoBox::set_max_qty(int mq) {
		if (mq < 0)
			throw std::invalid_argument("Максимальное кол-во патронов не может быть отрицательным. Попробуйте еще раз.");
		maxQty = mq;
		if (qty > maxQty) {
			qty = maxQty;
			set_weight(0);
		}
		return *this;
	}


	AmmoBox& AmmoBox::set_weight_of_one(double woo) {
		type.set_weigth(woo);
		set_weight(0);
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
		os << "Ящик с патронами; запас: " << qty << '\\' << maxQty << "; Вес: " << get_weight() << "; ";
		Item::print(os);
		return os;
	}

	std::ostream& AmmoBox::save(std::ostream& os) const noexcept {
		os << get_uP() << ' ' << qty << ' ' << maxQty << ' ' << type.get_weight() << ' ' << type.get_type() << '\n';
		return os;
	}

	std::istream& AmmoBox::load(std::istream& is) noexcept {
		int _int;
		double _double;
		std::string name;
		is >> _int;
		set_usedPoint(_int);
		is.ignore();
		is >> _int;
		set_qty(_int);
		is.ignore();
		is >> _int;
		set_max_qty(_int);
		is.ignore();
		is >> _double;
		set_weight_of_one(_double);
		is.ignore();
		std::getline(is, name);
		set_name(name);
		// Игнорируем всю оставшуюся строку, так, на всякий
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return is;
	}
}

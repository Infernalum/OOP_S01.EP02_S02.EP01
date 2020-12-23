#include "pch.h"

namespace XCom {

	Weapon::Weapon(const std::string& name, int up, int dam, int scat, double pen, int rad, const Ammo& ammo, int maxclip, double weight): Item(up) {
		if (dam < 0)
			throw std::invalid_argument("Урон от оружия не может быть отрицательным. Попробуйте еще раз.");
		if (scat < 0)
			throw std::invalid_argument("Показатель разброса не может быть отрицательным. Попробуйте еще раз.");
		if (pen < 0)
			throw std::invalid_argument("Штраф к попаданию на дистанции не может быть отрицательным. Попробуйте еще раз.");
		if (rad < 0)
			throw std::invalid_argument("Радиус действия оружия не может быть отрицательным. Попробуйте еще раз.");
		if (maxclip < 0)
			throw std::invalid_argument("Вместительность обоимы не может быть отрицательной. Попробуйте еще раз.");
		if (weight < 0)
			throw std::invalid_argument("Вес оружия не может быть отрицательным. Попробуйте еще раз.");
		marking = 'W';
		damage = dam;
		penalty = pen;
		radius = rad;
		maxClip = maxclip;
		clip = maxClip;
		weaponWeight = weight;
		set_weight(0);

	}

	/********************************************************/
	/*						Геттеры							*/
	/********************************************************/

	bool Weapon::empty() const noexcept {
		if (!clip)
			return true;
		else
			return false;
	}


	/********************************************************/
	/*						Сеттеры							*/
	/********************************************************/


	Weapon& Weapon::set_damage(int dam) {
		if (dam < 0)
			throw std::invalid_argument("Урон от оружия не может быть отрицательным. Попробуйте еще раз.");
		damage = dam;
		return *this;
	}


	Weapon& Weapon::set_scatter(int scat) {
		if (scat < 0)
			throw std::invalid_argument("Показатель разброса не может быть отрицательным. Попробуйте еще раз.");
		scatter = scat;
		return *this;
	}


	Weapon& Weapon::set_penalty(double pen) {
		if (pen < 0)
			throw std::invalid_argument("Штраф к попаданию на дистанции не может быть отрицательным. Попробуйте еще раз.");
		penalty = pen;
		return *this;
	}


	Weapon& Weapon::set_radius(int rad) {
		if (rad < 0)
			throw std::invalid_argument("Радиус действия оружия не может быть отрицательным. Попробуйте еще раз.");
		radius = rad;
		return *this;
	}


	Weapon& Weapon::set_max_clip(int mclip) {
		if (mclip <= 0)
			throw std::invalid_argument("Вместительность должна быть положительной. Попробуйте еще раз.");
		maxClip = mclip;
		if (clip > maxClip) {
			clip = maxClip;
			set_weight(0);
		}
		return *this;
	}


	Weapon& Weapon::set_clip(int cl) {
		if (cl < 0)
			throw std::invalid_argument("Кол-во патронов в обоиме не может быть отрицательным. Попробуйте еще раз.");
		if (cl > maxClip)
			clip = maxClip;
		clip = cl;
		set_weight(0);
		return *this;
	}


	Weapon& Weapon::set_weapon_weight(double w) {
		if (w < 0)
			throw std::invalid_argument("Вес оружия не может быть отрицательным. Попробуйте еще раз.");
		weaponWeight = w;
		return *this;
	}

	/********************************************************/
	/*					Остальные методы					*/
	/********************************************************/


	Weapon& Weapon::reloading(AmmoBox& ammobox) {
		int res = ammobox.using_item(maxClip - clip);
		set_clip(get_clip() + res);
		return *this;
	}


	int Weapon::using_item(int fictitious) {
		srand(time(0));
		int res = (damage - scatter) + rand() % (damage + scatter);
		if (res < 0)
			res = 0;
		if (res > 95)
			res = 95;
		return res;
	}

	std::pair<double, int> Weapon::calculate_the_hit(int distance) {
		srand(time(0));
		std::pair<double, int> res;
		double chance = 95;
		for (int i = 0; i < distance; ++i)
			chance *= (double)((100 - penalty) / 100);
		res.second = using_item(0);
		res.first = chance;
		return res;
	}

	std::ostream& Weapon::print(std::ostream& os) const noexcept {
		os << "Оружие: " << classifier << "; средний урон: " << damage << "; разброс урона: " << scatter << "; штраф к попаданию: " << penalty << "; радиус: " << radius << "; ";
		if (maxClip)
			os << "магазин: " << clip << "\\" << maxClip << "; тип патронов: " << type << "; вес оружия (без боеприпасов): " << weaponWeight << "; ";
		Item::print(os);
		return os;
	}


	std::ostream& Weapon::save(std::ostream& os) const noexcept {
		os << get_uP() << ' ' << damage << ' ' << scatter << ' ' << penalty << ' ' << radius << ' ' << maxClip << ' ' << clip << ' ' << weaponWeight << ' ' << classifier << '\n';
		os << type;
		return os;
	}

	std::istream& Weapon::load(std::istream& is) noexcept {
		int _int;
		double _double;
		std::string str;
		is >> _int;
		set_usedPoint(_int);
		is.ignore();
		is >> _int;
		set_scatter(_int);
		is.ignore();
		is >> _int;
		set_penalty(_int);
		is.ignore();
		is >> _int;;
		set_radius(_int);
		is.ignore();
		is >> _int;;
		set_max_clip(_int);
		is.ignore(); 
		is >> _int;
		set_clip(_int);
		is.ignore();
		is >> _double;
		set_weapon_weight(_double);
		set_weight(0);
		is.ignore();
		std::getline(is, str);
		set_classifier(str);
		is >> type;
		// Игнорируем всю оставшуюся строку, так, на всякий
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return is;
	}




}

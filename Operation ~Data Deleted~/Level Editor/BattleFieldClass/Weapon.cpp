#include "pch.h"

namespace XCom {

	Weapon::Weapon(const std::string& name, const Ammo& amm, int up, int dam, int scat, double pen, int rad, int maxclip, double weight) : Item(ITEMID_WEAPON, up) {
		if (dam < 0)
			throw std::invalid_argument("Урон от оружия не может быть отрицательным. Попробуйте еще раз.");
		if (scat < 0)
			throw std::invalid_argument("Показатель разброса не может быть отрицательным. Попробуйте еще раз.");
		if (scat > dam)
			throw std::invalid_argument("Показатель разброса не может быть больше среднего урона. Попробуйте еще раз.");
		if (pen < 0)
			throw std::invalid_argument("Штраф к попаданию на дистанции не может быть отрицательным. Попробуйте еще раз.");
		if (rad < 0)
			throw std::invalid_argument("Радиус действия оружия не может быть отрицательным. Попробуйте еще раз.");
		if (maxclip < 0)
			throw std::invalid_argument("Вместительность обоимы не может быть отрицательной. Попробуйте еще раз.");
		if (weight < 0)
			throw std::invalid_argument("Вес оружия не может быть отрицательным. Попробуйте еще раз.");
		classifier = name;
		damage = dam;
		scatter = scat;
		penalty = pen;
		radius = rad;
		maxClip = maxclip;
		clip = maxclip;
		weaponWeight = weight;
		ammo = amm;
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
		if (scat > damage)
			throw std::invalid_argument("ПОказатель разброса не может быть больше среднего урона. Попробуйте еще раз.");
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


	Weapon& Weapon::set_maxClip(int mclip) {
		if (mclip < 0)
			throw std::invalid_argument("Вместительность не может быть отрицательнойы. Попробуйте еще раз.");
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


	Weapon& Weapon::set_weaponWeight(double w) {
		if (w < 0)
			throw std::invalid_argument("Вес оружия не может быть отрицательным. Попробуйте еще раз.");
		weaponWeight = w;
		return *this;
	}

	void Weapon::set_weight(double frictious) {
		if (maxClip)
			Item::set_weight(weaponWeight + ammo.get_weight() * clip);
		else
			Item::set_weight(weaponWeight);
	}


	/********************************************************/
	/*					Остальные методы					*/
	/********************************************************/


	Weapon& Weapon::reloading(AmmoBox& ammobox) {
		if (!maxClip)
			throw std::logic_error("Нельзя перезаряжать оружие ближнего боя. Попробуйте еще раз.");
		if (ammobox.get_ammo() != ammo)
			throw std::invalid_argument("Неподходящий тип боеприпасов. Попробуйте еще раз.");
		int res = ammobox.using_item(maxClip - clip);
		set_clip(get_clip() + res);
		return *this;
	}


	int Weapon::using_item(int fictitious) {
		int res = (damage - scatter) + rand() % (damage + scatter);
		if (res < 0)
			res = 0;
		if (res > 95)
			res = 95;
		return res;
	}

	std::pair<double, int> Weapon::calculate_the_hit(int distance) {
		std::pair<double, int> res;
		double chance = 95;
		for (int i = 0; i < distance; ++i)
			chance *= (double)((100 - penalty) / 100);
		res.second = using_item(0);
		res.first = chance;
		return res;
	}

	std::ostream& Weapon::print(std::ostream& os) const noexcept {
		os << classifier;
		if (maxClip)
			os << " (" << clip << "\\" << maxClip << "); ";
		else
			os << "; ";
		os << "урон: " << damage - scatter << " - " << damage + scatter << "; штраф к расстоянию: " << penalty << "%; радиус: " << radius << "; ";
		if (maxClip)
			os << ammo;
		Item::print(os);
		return os;
	}


	std::ostream& Weapon::save(std::ostream& os) const noexcept {
		Item::save(os) << damage << ' ' << scatter << ' ' << penalty << ' ' << radius << ' ' << maxClip << ' ' << clip << ' ' << weaponWeight << ' ' << classifier << '\n';
		if (maxClip)
			ammo.save(os);
		return os;
	}

	std::istream& Weapon::load(std::istream& is) noexcept {
		Item::load(is) >> damage;
		is.ignore() >> scatter;
		is.ignore() >> penalty;
		is.ignore() >> radius;
		is.ignore() >> maxClip;
		is.ignore() >> clip;
		is.ignore() >> weaponWeight;
		is.ignore();
		std::getline(is, classifier);
		if (maxClip)
			ammo.load(is);
		set_weight(0);
		return is;
	}




}

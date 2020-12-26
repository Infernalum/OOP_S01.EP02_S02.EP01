#include "pch.h"

#include "Chryssalid.h"

namespace XCom {


	Chryssalid& Chryssalid::set_damage(int d) {
		if (d < 0)
			throw std::invalid_argument("Дамаг криссалида не может быть отрицательным. Пожалуйста, введите положительное число.");
		damage = d;
		return *this;
	}


	Chryssalid& Chryssalid::set_scatter(int scat) {
		if (scat < 0)
			throw std::invalid_argument("Разброс урона криссалида не может быть отрицательным. Пожалуйста, введите положительное число.");
		scatter = scat;
		return *this;
	}




	/********************************************************/
	/*					Остальные методы					*/
	/********************************************************/

	std::pair<bool, std::string> Chryssalid::attack(Operative* target) {
		std::pair<bool, std::string> res;
		res.first = false;
		int delta_x = abs(get_x() - target->get_x());
		int delta_y = abs(get_y() - target->get_y());
		int distance = delta_x + delta_y;
		if (distance <= 2) {
			// srand(time(0));
			// Шанс попадания
			double chance = 95 * (double)get_accurany() / 100 * (1 - (double)target->get_evasion() * 0.5);
			double range = 0 + rand() % 100;
			if (range > chance) {
				res.second = "Криссалид промахивается! Повезло.";
				return res;
			}
			int loss = (damage - scatter) + rand() % (damage + scatter);
			if (loss < 0)
				loss = 0;
			target->set_HP(target->get_HP() - loss);
			return res;
		}
		else {
			res.second = "Цель находится слишком далеко. Попробуйте еще раз.";
		}
	}


	std::ostream& Chryssalid::print(std::ostream& os) const noexcept {
		os << "Существо: Криссалид; ";
		Creature::print(os);
		os << " Урон в ближнем бою: " << damage - scatter << " - " << damage + scatter;
		return os;
	}


	std::ostream& Chryssalid::save(std::ostream& os) const noexcept {
		Creature::save(os);
		os << damage << ' ' << scatter << '\n';
		return os;
	}

	std::istream& Chryssalid::load(std::istream& is) noexcept {
		Creature::load(is);
		is >> damage;
		is.ignore() >> scatter;
		return is;
	}

}

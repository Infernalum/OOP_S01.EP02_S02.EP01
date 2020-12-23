#include "pch.h"

namespace XCom {

	Porter::~Porter() {
		if (!items.empty())
			for (auto iter = items.begin(); iter != items.end(); ++iter) {

			}

	}


	std::ostream& Porter::print(std::ostream& os) const {
		os << "Существо: фуражир; ";
		Creature::print(os);
		if (items.empty()) {
			os << "Инвентарь пуст.";
		}
		else {
			os << "Вещи в инвентаре:\n";
			int i = 1;
			for (auto iter = items.begin(); iter != items.end(); ++iter)
				os << "Предмет #" << i << "; " << *iter;
		}
		return os;
	}


	std::istream& Porter::load(std::istream& is) noexcept {
		items.clear();
		Creature::load(is);
		int size;
		is >> size;
		is.ignore();
		std::string marks;
		std::getline(is, marks);
		for (int i = 0; i < size; ++i) {
			Item* ptr = nullptr;
			char name = marks[i];
			if (name == 'F') {
				ptr = new FirstAidKit;
				ptr->load(is);
			}
			else if (name == 'A') {
				ptr = new AmmoBox;
				ptr->load(is);
			}
			else if (name == 'W') {
				ptr = new Weapon;
				ptr->load(is);
			}
			items.push_back(ptr);
		}
		return is;
	}


	std::ostream& Porter::save(std::ostream& os) const noexcept {
		Creature::save(os);
		os << items.size() << '\n';
		if (!items.empty())
			// Записываем строку предметов
			for (auto iter = items.begin(); iter != items.end(); ++iter)
				os << (*iter)->get_name();
		os << '\n';
		for (auto iter = items.begin(); iter != items.end(); ++iter)
			os << *iter;
		return os;
	}


}

#include "pch.h"

namespace XCom {


	Porter& Porter::operator =(const Porter& copy) noexcept {
		if (this != &copy) {
			inventory = copy.inventory;
			starages = copy.starages;
		}
		return *this;
	}


	Porter& Porter::operator =(Porter&& move) noexcept {
		inventory.swap(move.inventory);
		starages.swap(move.starages);
		return *this;
	}



	double Porter::total_weight() const noexcept {
		double res = 0;
		for (int i = 0; i < inventory.size(); ++i)
			res += inventory[i]->get_weight();
		return res;
	}

	std::ostream& Porter::show_table(std::ostream& os) const noexcept {
		if (inventory.empty()) {
			os << "Инвентарь пуст.\n";
		}
		else {
			os << "Инвентарь:\n";
			int i = 1;
			for (auto iter = inventory.begin(); iter != inventory.end(); ++iter)
				os << " #" << i++ << ": " << **iter << '\n';
		}
		return os;
	}


	Item* Porter::drop_item(int pos) {
		if (pos < 1 || pos > inventory.size())
			throw std::out_of_range("Предмета с таким номером нет в инвентаре. Попробуйте еще раз.");
		Item* res = inventory[pos--];
		inventory.erase(inventory.begin() + pos);
		return res;
	}



	Item* Porter::select_item(int pos) {
		if (pos < 1 || pos > inventory.size())
			throw std::out_of_range("Предмета с таким номером нет в инвентаре. Попробуйте еще раз.");
		return inventory[pos--];
	}





	std::ostream& Porter::print(std::ostream& os) const noexcept {
		os << "Существо: фуражир; ";
		Creature::print(os);
		show_table(os);
		return os;
	}


	std::ostream& Porter::save(std::ostream& os) const noexcept {
		Creature::save(os);
		os << inventory.size() << '\n';
		// Записываем строку предметов
		for (auto iter = inventory.begin(); iter != inventory.end(); ++iter)
			(*iter)->save(os);
		return os;
	}


	std::istream& Porter::load(std::istream& is) noexcept {
		for (auto iter = inventory.begin(); iter != inventory.end(); ++iter)
			delete* iter;
		inventory.clear();
		Creature::load(is);
		int size;
		is.ignore() >> size;
		is.ignore();
		int ID;
		for (int i = 0; i < size; ++i) {
			Item* ptr = nullptr;
			is >> ID;
			is.ignore();
			switch (ID) {
			case ITEMID_AMMOBOX:
				ptr = new AmmoBox;
				ptr->load(is);
				break;
			case ITEMID_FIRSTAIDKIT:
				ptr = new FirstAidKit;
				ptr->load(is);
				break;
			case ITEMID_WEAPON:
				ptr = new Weapon;
				ptr->load(is);
				break;
			}
			inventory.push_back(ptr);
		}
		return is;
	}


}

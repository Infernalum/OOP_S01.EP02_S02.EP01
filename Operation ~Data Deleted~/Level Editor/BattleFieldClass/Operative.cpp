#include "pch.h"


namespace XCom {


	// Начинаем с символа 'A' 
	char Operative::idGenerator = 'A';

	Operative& Operative::operator =(const Operative& copy) noexcept {
		if (this != &copy) {
			callname = copy.callname;
			spriteID = copy.spriteID;
			inventory = copy.inventory;
			hand = copy.hand;
		}
		return *this;
	}


	Operative& Operative::operator =(Operative&& move) noexcept {
		callname.swap(move.callname);
		char tmp = move.spriteID;
		move.spriteID = spriteID;
		spriteID = tmp;
		inventory.swap(move.inventory);
		Weapon* wp = move.hand;
		move.hand = hand;
		hand = wp;
		return *this;
	}


	std::ostream& Operative::print(std::ostream& os) const noexcept {
		os << "Оперативник: " << callname << "; ";
		Creature::print(os);
		os << " Оружие в руке: ";
		if (hand)
			os << *hand;
		else
			os << "нет;";
		os << '\n';
		show_table(os);
		return os;
	}


	Weapon* Operative::change_weapon(Weapon* weapon) noexcept {
		Weapon* _old = hand;
		hand = weapon;
		return _old;
	}


	double Operative::total_weight() const noexcept {
		double res = 0;
		for (auto iter = inventory.begin(); iter != inventory.end(); ++iter)
			res += iter->get_weight();
		return res;
	}


	std::ostream& Operative::show_table(std::ostream& os) const noexcept {
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


	Item* Operative::drop_item(int pos) {
		if (pos < 1 || pos > inventory.size())
			throw std::out_of_range("Предмета с таким номером нет в инвентаре. Попробуйте еще раз.");
		Item* res = inventory[pos--];
		inventory.erase(inventory.begin() + pos);
		return res;
	}


	Item* Operative::select_item(int pos) {
		if (pos < 1 || pos > inventory.size())
			throw std::out_of_range("Предмета с таким номером нет в инвентаре. Попробуйте еще раз.");
		return inventory[pos--];
	}



	std::ostream& Operative::save(std::ostream& os) const noexcept {
		Creature::save(os);
		if (hand) {
			os << 1 << ' ';
			hand->save(os);
		}
		else
			os << 0 << ' ';
		os << inventory.size() << '\n';
		for (auto iter = inventory.begin(); iter != inventory.end(); ++iter)
			(*iter)->save(os);
		return os;
	}



	std::istream& Operative::load(std::istream& is) noexcept {
		Creature::load(is);
		int state;
		is.ignore() >> state;
		if (state) {
			Weapon* wp = new Weapon;
			// Скипаем идентификатор предмета
			is.ignore() >> state;
			is.ignore();
			wp->load(is);
			hand = wp;
		}
		else
			is.ignore();
		is >> state;
		is.ignore();
		int ID;
		for (int i = 0; i < state; ++i) {
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

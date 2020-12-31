#include "pch.h"






namespace XCom {



	/********************************************************/
	/*					Конструкторы						*/
	/********************************************************/

	/* ВНИМАНИЕ!!!! Насчет копирующих и перемещающих конструкторов
		Так как класс клетка в моей реализации представляется отдельным (а значит, самостоятельным) объектом
	необходимо описать конструкторы так, чтобы с клеткой можно было работать как с отдельным объектом,
	а не частью игрового поля. Путем геморроя отладки и осознания собственной тупости, до меня наконец
	дошло, что copy- и move- конструкторы юзаются очень часто (при создании поля в функции и передаче его
	в main, при сохранении/загрузке в файл/из файла и т.д.). Поэтому:
		Что делает копирующий конструктор: он производит копирование полей клетки.
	То есть НЕ создает копии существа и вещей из списка дропнутых предметов. А => юзер сам должен контролировать и отслеживать
	указатели на предметы и существо.
		Что делает перемещающий конструктор: работает по дефолту (меняет все указатели местами), тут ничего сверъестественного
		Что делает деструктор: точно так же НЕ удаляет привязанное существо, но удаляет дропнутые предметы (ибо кроме как в этой клетке
		информации о них больше нигде нет)
	*/


	// Конструктор по умолчанию: создает клетку символа "пол", который задан в спрайтах карты как первый символ
	Cell::Cell() noexcept :
		species(Level::get_sprites()[0]),
		itemList(),
		creature(),
		fog(true),
		visible(true) {};


	// Конструктор, задающий тип спрайта (Задавать указатель на существо во время инициализации поля НЕЛЬЗЯ априори; поэтому он всегда nullptr. Кроме того, индекс спрайта должен существовать)
	Cell::Cell(int iSprites) : fog(false), visible(false) {
		if (iSprites < 0 || iSprites >= (int)Level::get_sprites().size())
			throw std::out_of_range("Клетки такого типа не существует. Попробуйте еще раз.");
		species = Level::get_sprites()[iSprites];
		creature = nullptr;
	}


	// Копирующий конструктор (В соответсвиями с описанием выше)
	Cell::Cell(const Cell& copy) noexcept :
		fog(copy.fog),
		visible(copy.visible),
		species(copy.species),
		creature(copy.creature),
		itemList() {
		// Так как деструктор клетки будет удалять список дропнутых вещей, что для правильной реализации копирования надо именно продублировать вещи своими копиями
		for (auto iter = copy.itemList.begin(); iter != copy.itemList.end(); ++iter)
			itemList.push_back((*iter)->clone());
	}


	// Копирующий оператор присваивания: точно так же не удаляет уже привязанное существо
	Cell& Cell::operator = (const Cell& copy) noexcept {
		if (this != &copy) {
			fog = copy.fog;
			visible = copy.visible;
			species = copy.species;
			creature = copy.creature;
			for (auto iter = copy.itemList.begin(); iter != copy.itemList.end(); ++iter)
				itemList.push_back((*iter)->clone());
		}
		return *this;
	}


	// Перемещающий оператор присваивания
	Cell& Cell::operator = (Cell&& move) noexcept {
		std::swap(species, move.species);
		std::swap(fog, move.fog);
		std::swap(visible, move.visible);
		Creature* tmpCreature = move.creature;
		move.creature = creature;
		creature = tmpCreature;
		itemList.swap(move.itemList);
		return *this;
	}


	// Дестуктор (Подразумевается, что при удалении привязанное существо остается в памяти, а вот трупы так как не имеют больше связи ни с чем, удаляются вместе с клеткой)
	Cell::~Cell() {
		if (!itemList.empty())
			for (auto iter = itemList.begin(); iter != itemList.end(); ++iter)
				delete (*iter);
		itemList.clear();
	}


	/********************************************************/
	/*						Геттеры							*/
	/********************************************************/


	/********************************************************/
	/*						Сеттеры							*/
	/********************************************************/

	// Изменить тип клетки
	Cell& Cell::set_species(char type) {
		if (Level::get_sprites().find_first_of(type) == std::string::npos)
			throw std::out_of_range("Вы пытаетесь изменить тип клетки на несуществующий. Пожалуйста, выберите/измените спрайты класса \"Уровень\"");
		species = type;
		return *this;
	}


	// Установить указатель на существо (вернет exception, если уже есть указатель на существо)
	Cell& Cell::set_creature(Creature* ptr) {
		auto pos = Level::get_sprites().find_first_of(species);
		if (pos == 1 || pos == 2 || pos == 3)
			throw std::invalid_argument("На данном типе клетки нельзя расположить существо. Выберите другую клетку.");
		if (creature)
			throw std::invalid_argument("На данной клетке уже кто-то есть. Выберите другую клетку.");
		creature = ptr;
		return *this;
	}


	// Получить указатель на конкретный предмет из списка вещей (передается НОМЕР предмета)
	Item* Cell::get_item(int pos) const {
		if (!itemList.size())
			throw std::out_of_range("Здесь нет никаких предметов. Попробуйте еще раз.");
		if (pos < 1)
			throw std::out_of_range("Предмета с таким номером быть не может. Попробуйте еще раз");
		if (pos > itemList.size())
			throw std::out_of_range("Предмета с таким номером на клетке нет. Попробуйте еще раз.");
		auto item = itemList.begin();
		for (int i = 1; i < pos; ++i)
			++item;
		return *item;
	}

	// Вывести список предметов на клетке
	std::ostream& Cell::show_list(std::ostream& os) const noexcept {
		if (!itemList.size())
			os << "вещей нет." << '\n';
		int i = 1;
		for (auto iter = itemList.begin(); iter != itemList.end(); ++iter)
			os << "№" << i++ << ": " << **iter << '\n';
		return os;
	}


	/********************************************************/
	/*					Остальные методы					*/
	/********************************************************/


	// Удалить и вернуть указатель на существо, в случае, если оно передвинулось или было уничтожено (УДАЛЕТСЯ НЕ СУЩЕСТВО, А ЗАНУЛЯЕТСЯ УКАЗАТЕЛЬ КЛЕТКИ!!!!); exception, если указатель пуст, не будет, просто выполение ничего не даст
	Creature* Cell::loose_creature() noexcept {
		Creature* tmp = creature;
		creature = nullptr;
		return tmp;
	}


	// Удалить какой-то предмет из списка вещей (задается номером вещи в списке, т.к. игроку будет выводиться игроку); вызывается exception, если предмет с таким номером не существует или список пуст 
	Item* Cell::erase_item(int n) {
		if (n < 1)
			throw std::exception("Предмета с таким номером быть не может. Попробуйте еще раз.");
		int size = itemList.size();
		if (!size)
			throw std::exception("Здесь нет никаких предметов. Попробуйте еще раз.");
		if (n > size)
			throw std::exception("Предмета с таким номером здесь нет. Попробуйте еще раз.");
		int i = 1;
		for (auto iter = itemList.begin(); i <= n; iter++) {
			if (i == n) {
				// Сохраняем адрес удаляемой вещи
				Item* res = *iter;
				itemList.erase(iter);
				// Возвращаем его для дальнейшего использования
				return res;
			}
		}
	}


	// Вывод клетки
	std::ostream& operator << (std::ostream& os, const Cell& cell) {
		// Если она невидима глобально (fog true), то знак '?' (невидимость)
		if (!cell.fog)
			os << '?';
		// Если она была засвечена, но в данный момент невидима(visible false), то отображается тип клетки;
		else if (!cell.visible)
			os << cell.get_species();
		// Если она была засвечена, и засвечена до сих пор (visible true), то отображается либо враг, стоящий на ней, либо предметы, если врага нет, либо тип клетки, если ни того, ни другого нет
		else {
			if (cell.creature)
				if (cell.creature->get_ID() != CREATUREID_OPERATIVE)
					os << Level::get_markingAliens()[cell.creature->get_ID()];
				else
					os << dynamic_cast<Operative*>(cell.creature)->get_spriteID();
			else if (!cell.empty())
				os << Level::get_sprites()[5];
			else
				os << cell.get_species();
		}
		return os;
	}


	std::ostream& Cell::save(std::ostream& os) const noexcept {
		os << get_species() << ' ' << itemList.size() << '\n';
		for (auto iter = itemList.begin(); iter != itemList.end(); ++iter)
			(*iter)->save(os);
		return os;
	}

}


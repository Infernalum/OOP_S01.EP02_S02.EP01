#include "pch.h"
#include "Cell.h"





namespace Battlefield {



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
		creature() {};


	// Конструктор, задающий тип спрайта (Задавать указатель на существо во время инициализации поля НЕЛЬЗЯ априори; поэтому он всегда nullptr. Кроме того, индекс спрайта должен существовать)
	Cell::Cell(int iSprites) {
		if (iSprites < 0 || iSprites >= Level::get_sprites().size())
			throw std::out_of_range("Клетки такого типа не существует. Попробуйте еще раз.");
		species = Level::get_sprites()[iSprites];
		creature = nullptr;
	}

	// Копирующий конструктор (В соответсвиями с описанием выше)
	Cell::Cell(const Cell& copy) noexcept :
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
			species = copy.species;
			creature = copy.creature;
			for (auto iter = copy.itemList.begin(); iter != copy.itemList.end(); ++iter)
				itemList.push_back((*iter)->clone());
		}
		return *this;
	}


	/*
		Перемещающий конструктор (НЕ удаляет ничего, что связано с клеткой)
		Единственное принципиальное отличие в том, что предметы не копируются, а перепривязываются к клетке
	*/
	Cell::Cell(Cell&& move) noexcept :
		species(move.species),
		creature(move.creature),
		itemList(move.itemList) {
		move.creature = nullptr;
		move.itemList.clear();
	}


	// Перемещающий оператор присваивания
	Cell& Cell::operator = (Cell&& move) noexcept {
		char tmpSpecies = move.species;
		move.species = species;
		species = tmpSpecies;
		Creature* tmpCreature = move.creature;
		move.creature = creature;
		creature = tmpCreature;
		std::list<Item*> tmpList = move.itemList;
		move.itemList = itemList;
		itemList = tmpList;
		return *this;
	}


	// Дестуктор (Подразумевается, что при удалении привязанное существо остается на поле, а вот дропнутые предметы так как не имеют больше связи ни с чем, удаляются вместе с клеткой)
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
			throw std::exception("Предмета с таким номером тут быть не может.");
		int size = itemList.size();
		if (!size)
			throw std::exception("Здесь нет никаких предметов.");
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


	/*
			int size = cell.itemList.size();
		if (!size)
			os << "Здесь нет вещей.";
		else
			for (auto iter = cell.itemList.begin(); iter != cell.itemList.end(); ++iter)
				os << "Предмет #" << size++ << ": " << (*iter) << ";\n";
		return os;
	*/


	// Вывод клетки
	std::ostream& operator << (std::ostream& os, const Cell& cell) {
		os << cell.get_species();
		return os;
	}


}


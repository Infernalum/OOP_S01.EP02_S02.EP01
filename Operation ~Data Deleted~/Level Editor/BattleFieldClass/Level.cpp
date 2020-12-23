#include "pch.h"

#include "Level.h"



namespace XCom {

	const std::string Level::sprites = ".#-=&!";

	/********************************************************/
	/*					Конструкторы						*/
	/********************************************************/


	/*
	Копирующий конструктор
		Мы копируем поле (юзая копирующий конструтор для клеток), создаем копии существ из списков тим и перепривязываем всех существ к их клеткам.
		Таким образом, старые указатели на существ из копирующего поля поменяются на указатели на копии существ
	*/
	Level::Level(const Level& copy) noexcept : field(copy.field), ammo(copy.ammo) {
		for (auto iter = copy.squadAliens.begin(); iter != copy.squadAliens.end(); ++iter) {
			Creature* tmp = (*iter)->clone();
			squadAliens.push_back(tmp);
			field[tmp->change_coords().second][tmp->change_coords().first].set_creature(tmp);
		}
		for (auto iter = copy.squadOperative.begin(); iter != copy.squadOperative.end(); ++iter) {
			Creature* tmp = (*iter)->clone();
			squadAliens.push_back(tmp);
			field[tmp->change_coords().second][tmp->change_coords().first].set_creature(tmp);
		}
	}


	// Копирующий оператор присваивания
	Level& Level::operator =(const Level& copy) noexcept {
		if (this != &copy) {
			field = copy.field;
			ammo = copy.ammo;
			for (auto iter = copy.squadAliens.begin(); iter != copy.squadAliens.end(); ++iter) {
				Creature* tmp = (*iter)->clone();
				squadAliens.push_back(tmp);
				field[tmp->change_coords().second][tmp->change_coords().first].set_creature(tmp);
			}
			for (auto iter = copy.squadOperative.begin(); iter != copy.squadOperative.end(); ++iter) {
				Creature* tmp = (*iter)->clone();
				squadAliens.push_back(tmp);
				field[tmp->change_coords().second][tmp->change_coords().first].set_creature(tmp);
			}
		}
		return *this;
	}


	// Перемещающий оператор присваивания
	Level& Level::operator =(Level&& move) noexcept {
		field.swap(move.field);
		squadAliens.swap(move.squadAliens);
		squadOperative.swap(move.squadOperative);
		return *this;
	}


	/*
	Деструктор
		Порядок удаления: удаление существ из обеих тим, а потом удаление поля, т. е. каждой клетки со списком дропнутых предметов, так что все норм
		Для существ,имеющих инвентарь: удаляется инвентарь (НЕ ПУТАТЬ С УНИЧТОЖЕНИЕМ СУЩЕСТВА! В ЭТОМ СЛУЧАЕ ВЕЩИ ИЗ СУЩЕСТВА ВЫПАДАЮТ НА КЛЕТКУ)
	*/
	Level::~Level() {
		for (auto iter = squadAliens.begin(); iter != squadAliens.end(); ++iter)
			delete (*iter);
		for (auto iter = squadOperative.begin(); iter != squadOperative.end(); ++iter)
			delete (*iter);
		field.clear();
	}

	/********************************************************/
	/*						Геттеры							*/
	/********************************************************/


	// Вывести список символов, отвечающих за спрайты (для того, чтобы игрок знал, что что обозначает)
	const std::ostream& Level::print_sptites(std::ostream& os) const noexcept {
		os << " [" << sprites[0] << "] - пол;\n [" << sprites[1] << "] - стена;\n [" << sprites[2] << "] - стекло;\n [" << sprites[3] << "] - перегородка;\n [" << sprites[4] << "] - складская точка пришельцев;";
		return os;
	}



	/********************************************************/
	/*						Сеттеры							*/
	/********************************************************/


	// Устанавливает размеры игрового поля (и создает соотв. поле из клеток по умолчанию); при создании нового поля, старое стирается
	Level& Level::set_proportions(int n, int m) {
		// n - ШИРИНА, m - ДЛИНА (в силу специфики создания двумерного вектора)
		if (n < 1 || m < 1)
			throw std::exception("Поле с заданными пропорциями существовать не может. Попробуйте еще раз.");
		for (auto iter = squadAliens.begin(); iter != squadAliens.end(); ++iter)
			delete (*iter);
		for (auto iter = squadOperative.begin(); iter != squadOperative.end(); ++iter)
			delete (*iter);
		squadAliens.clear();
		squadOperative.clear();
		field.clear();
		field.resize(m);
		for (int i = 0; i < m; ++i)
			field[i].resize(n);
		return *this;
	}


	// Позволяет изменить тип конкретной клетки, задающейся коор-тами x и y
	Level& Level::set_cell(int x, int y, int type) {
		if (--x < 0 || x >= (int)field[0].size())
			throw std::exception("Координата x вне границ карты. Попробуйте еще раз.");
		if (--y < 0 || y >= (int)field.size())
			throw std::exception("Координата y вне границ карты. Попробуйте еще раз.");
		field[y][x].set_species(sprites[--type]);
		return *this;
	}


	// Добавляем существо в тиму и на поле
	Level& Level::add_to_level(Creature* cr, int x, int y) {
		if (--x < 0 || --y < 0 || x >= (int)field[0].size() || y >= (int)field.size())
			throw std::exception("Координаты клетки введены неверно. Выберите другую клетку.");
		// Исключения, что на данной клетке уже есть существо или тип клетки не позволяет размещать его, выбрасываются в set_creature()
		field[y][x].set_creature(cr);
		if (cr->name() == 'A')
			squadOperative.push_back(cr);
		else
			squadAliens.push_back(cr);
		cr->change_coords().first = x;
		cr->change_coords().second = y;
		return *this;
	}


	// Отвязать существо от клетки (возвращает nullptr, если существа нет, и адрес существа в противном случае)
	Creature* Level::loose_creature(int x, int y) {
		if (--x < 0 || --y < 0 || x >= (int)field[0].size() || y >= (int)field.size())
			throw std::exception("Координаты клетки введены неверно. Выберите другую клетку.");
		Creature* res = field[x][y].loose_creature();
		return res;
	}


	/********************************************************/
	/*					Другие методы						*/
	/********************************************************/

	// Ввод игрового поля
	std::istream& operator >> (std::istream& is, Level& field) {
		std::string data;
		int n = field.field[0].size();
		int m = field.field.size();
		for (int i = 0; i < m; ++i) {
			int cur = n;
			is >> data;
			auto pos = data.find_first_not_of(field.sprites);
			if (pos != std::string::npos && (int)pos < cur)
				cur = pos;
			int size = data.size();
			if (size < cur)
				cur = size;
			for (int j = 0; j < cur; ++j)
				field.field[i][j].set_species(data[j]);
			data.clear();
		}
		return is;
	}


	// Вывод игрового поля
	std::ostream& operator << (std::ostream& os, const Level& field) {
		int n = field.field[0].size();
		int  m = field.field.size();
		// Выводим координаты по X
		os << ' ';
		for (int i = 1; i <= n; ++i) {
			int c = i, first;
			while (c > 0) {
				first = c % 10;
				c /= 10;
			}
			os << first;
		}
		os << '\n';
		for (int i = 0; i < m; ++i) {
			int c = i + 1, first;
			while (c > 0) {
				first = c % 10;
				c /= 10;
			}
			os << first;
			for (int j = 0; j < n; ++j)
				if (field.field[i][j].get_creature())
					if (field.field[i][j].get_creature()->name() == 0)
						os << field.field[i][j].get_creature()->name();
					else
						os << field.field[i][j].get_creature()->name();
				else
					os << field.field[i][j];
			os << '\n';
		}
		return os;
	}


}


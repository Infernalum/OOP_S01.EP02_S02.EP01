#include "pch.h"

#include "Level.h"



namespace XCom {

	const std::string Level::sprites = ".#-=&!";

	const std::string Level::markingAliens = "pcm";

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
			field[tmp->get_y()][tmp->get_x()].set_creature(tmp);
		}
		for (auto iter = copy.squadOperative.begin(); iter != copy.squadOperative.end(); ++iter) {
			Creature* tmp = (*iter)->clone();
			squadAliens.push_back(tmp);
			field[tmp->get_y()][tmp->get_x()].set_creature(tmp);
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
				field[tmp->get_y()][tmp->get_x()].set_creature(tmp);
			}
			for (auto iter = copy.squadOperative.begin(); iter != copy.squadOperative.end(); ++iter) {
				Creature* tmp = (*iter)->clone();
				squadAliens.push_back(tmp);
				field[tmp->get_y()][tmp->get_x()].set_creature(tmp);
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
		if (cr->get_ID() == CREATUREID_OPERATIVE)
			squadOperative.push_back(cr);
		else
			squadAliens.push_back(cr);
		cr->set_x(x);
		cr->set_y(y);
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


	/*
		Процесс уничтожения (смерти) существа: для каждого класса существа свой процесс стирания его с поля.
	(ВНИМАНИЕ! ПРИ ДОБАВЛЕНИИ НОВОГО КЛАССА СУЩЕСТВА СЮДА НЕОБХОДИМО ДОБАВИТЬ СООТВЕТСВУЮЩИЙ КЕЙС!!!)
	*/
	Level& Level::destruction(Creature*& target) {

		return *this;
	}



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


	std::ostream& Level::save(std::ostream& os) {
		os << squadOperative.size() << '\n';
		for (auto iter = squadOperative.begin(); iter != squadOperative.end(); iter++)
			(*iter)->save(os);
		os << squadAliens.size() << '\n';
		for (auto iter = squadAliens.begin(); iter != squadAliens.end(); iter++)
			(*iter)->save(os);
		int n = field[0].size();
		int  m = field.size();
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				field[j][i].save(os);
			}
		return os;
	}


	// Вывод игрового поля
	std::ostream& operator << (std::ostream& os, const Level& field) {
		int n = field.field[0].size();
		int  m = field.field.size();
		// Выводим координаты по X
		os << ' ' << ' ';
		for (int i = 1; i <= n; ++i) {
			int c = i, first;
			while (c > 0) {
				first = c % 10;
				c /= 10;
			}
			os << first;
		}
		os << '\n' << ' ' << ' ';
		for (int i = 1; i <= n; ++i)
			os << '-';
		os << '\n';
		for (int i = 0; i < m; ++i) {
			int c = i + 1, first;
			while (c > 0) {
				first = c % 10;
				c /= 10;
			}
			os << first << '|';
			for (int j = 0; j < n; ++j)
				os << field.field[i][j];
			os << '\n';
		}

		os << " Команда оперативников:\n";
		if (!field.squadOperative.size())
			std::cout << "Команда пуста;\n";
		else
			for (auto iter = field.squadOperative.begin(); iter != field.squadOperative.end(); iter++)
				std::cout << **iter << '\n';

		os << " Команда Пришельцев:\n";
		if (!field.squadAliens.size())
			std::cout << "Команда пуста;\n";
		else
			for (auto iter = field.squadAliens.begin(); iter != field.squadAliens.end(); iter++)
				std::cout << **iter << '\n';
		os << "\n Предметы на земле:\n";
		bool check = false;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				if (!field.field[j][i].empty()) {
					os << "Клетка (" << i << "\\" << j << "):\n";
					field.field[j][i].show_list(os);
					check = true;
				}
			}
		if (!check)
			os << "Нет предметов.\n";

		os << '\n';
		return os;
	}


}


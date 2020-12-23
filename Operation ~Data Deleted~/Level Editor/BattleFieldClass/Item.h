#ifndef ITEM_H
#define ITEM_H


namespace XCom {

	// Базовый абстрактный класс "Предмет"
	class Item {

		// Кол-во очков, которые нужно потратить, чтобы заюзать предмет (выстрелить, захилиться, перезарядиться и тд)
		int usedPoint;

		// Вес предмета (считается отдельно, т.к. для аптечки и оружейного ящика (да и для оружия) вес высчитывается с учетом сотояния дочерних классов
		double weight;

	protected:

		virtual std::ostream& print(std::ostream&) const noexcept;

		char marking;

	public:

		/* Правило: никогда не вызывать виртуальные функции в теле конструкторов или деструкторов базовых классов */

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		// Копирующие/перемещающие конструкторы по умолчанию

		// Единственный конструктор
		Item(int uP = 1);

		// Виртуальный деструктор
		virtual ~Item() {};

		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/

		double get_weight() const noexcept { return weight; };
		int get_uP() const noexcept { return usedPoint; };
		char get_name() const noexcept { return marking; };


		/********************************************************/
		/*						Сеттеры							*/
		/********************************************************/

		// Изменение веса предмета (для каждого типа предмета свой метод подсчета веса, а это служит только для явной переустановки)
		virtual void set_weight(double);

		/*
			Использование предемета.
		Для оружейного ящика: вытащить n патронов из ящика; в случае, если в ящике меньше патронов, вытаскивается кол-во, которое можно забрать
		Для аптечки: использовать аптечку (после использования аптечка удаляется)
		Для оружия: выстрелить 1-им патроном. Вычисляется шанс попадания для расстояния в n клеток
		*/
		virtual int using_item(int) = 0;

		void set_usedPoint(int);

		/********************************************************/
		/*					Остальные методы					*/
		/********************************************************/

		// Чисто виртуальный метод сохранения информации о предмете в выходной/файловый поток
		virtual std::ostream& save(std::ostream&) const noexcept = 0;

		// Чисто виртуальный метод загрузки информации о предмете из входного/файлового потока
		virtual std::istream& load(std::istream&) noexcept = 0;

		// Создание копии предмета
		virtual Item* clone() const noexcept = 0;

		friend std::ostream& operator << (std::ostream& os, const Item& c) { return c.print(os); };

	};


	// Вспомогательный класс "Патрон"
	class Ammo {

		std::pair<std::string, double> type;

	public:

		// Начальная инициализация патрона
		static const std::pair<std::string, double> _default;

		// Пустой конструктор, который создает тип обычного автоматного (СУЩЕСТВУЮЩЕГО В ИГРЕ) патрона
		Ammo() noexcept : type(_default) {};

		// Конструктор с явным заданием параметров
		Ammo(const std::string&, double weight = 0.01);

		// Конструктор преобразования
		Ammo(const std::pair<std::string, double>&);

		std::string get_type() const noexcept { return type.first; };
		double get_weight() const noexcept { return type.second; };

		Ammo& set_type(const std::string& name) noexcept { type.first = name; return *this; };
		Ammo& set_weigth(double);

		// Сохранение информации о типе патрона в выходной/файловый поток
		std::ostream& save(std::ostream&) const noexcept;
		// Загрузка информации о типе патрона из входного/файлового
		std::istream& load(std::istream&) noexcept;

		// Для работы find() в векторе типов патронов (чтобы гарантировать индивидуальность типов патронов)
		bool operator ==(const Ammo& cur) noexcept{ return type == cur.type; };
		// Вывод информации о типе патрона (не для сохранения в файл)
		friend std::ostream& operator <<(std::ostream&, const Ammo&) noexcept;
		// Загрузка информации о типе патрона из входного/файлового
		friend std::istream& operator >>(std::istream& is, Ammo& ammo) noexcept { return ammo.load(is); };
	};




}

#endif // !_ITEM_H_




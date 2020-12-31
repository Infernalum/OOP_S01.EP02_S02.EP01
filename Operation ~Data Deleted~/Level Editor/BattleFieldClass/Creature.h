#ifndef CREATURE_H
#define CREATURE_H


namespace XCom {


	/*
		Перечисление типов существ. У каждого оперативника свой индивидуальный чар спрайта,
	а вот пришельцы одного типа не должны друг от друга отличаться (начинаем с нуля, чтобы индексация в спрайтах пришельцев работала дефолтно)
	*/
	enum CreatureID {
		CREATUREID_OPERATIVE = -1,
		CREATUREID_PORTER,
		CREATUREID_CHRYSSALID,
		CREATUREID_MUTON,
	};


	// Базовый абстрактный класс "Существо"
	class Creature {

		// Координаты клетки, на которой стоит существо
		std::pair<int, int> coords;
		// Текущее \ максимальное кол-во очков здоровья
		int HP, maxHP;
		// Параметр уклонения существа: снижает шанс попадания (варьируется от 0 - нет бонуса, до 100% - уменьшает шанс в 2 раза)
		int evasion;
		// Параметр точности существа: показывает, каков шанс нанести урон от стандартного шанса оружием. 0 - шансов нет (ослеплен), 100 - обычная точность
		int accuracy;
		// Текущее \ максимальное кол-во очков времени
		int TP, maxTP;
		// Радиус обзора существа
		int sight;

	protected:

		// Идентификатор существа (см. enum CreatureID)
		int ID;

		/*
			В protected область добавляем функцию вывода, чтобы доступ к ней имели и дочерние классы,
		но напрямую обращаться к ней было нельзя, т.е. вывод происходил только через перегруженный оператор
		То есть, при вызове перегруженного оператора вывода в дочерних классах будет вызываться ИХ метод print,
		а при использовании в них вывода для абстрактного класса, будет использоваться метод print базового класса.
		*/
		virtual std::ostream& print(std::ostream&) const noexcept;


	public:

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		// Конструктор существа по умолчанию; менять максимальные хар-ки будем через сеттеры
		Creature(int t = -1, int s = 1, int mh = 1, int mtp = 1, int mw = 1)
			: ID(t), coords{ -1,-1 }, evasion(0), accuracy(100) { set_sight(s); set_maxHP(mh), set_HP(mh), set_maxTP(mtp), set_TP(mtp); };


		// Виртуальная функция создания копии существа
		virtual Creature* clone() const noexcept = 0;

		// Виртуальный деструктор
		virtual ~Creature() {};

		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/

		// Получение базовых характеристик абстрактного класса

		int get_ID() const noexcept { return ID; };
		int get_x() const noexcept { return coords.first; };
		int get_y() const noexcept { return coords.second; };
		int get_HP() const noexcept { return HP; };
		int get_TP() const noexcept { return TP; };
		int get_maxTP() const noexcept { return maxTP; };
		int get_maxHP() const noexcept { return maxHP; };
		int get_sight() const noexcept { return sight; };
		int get_evasion() const noexcept { return evasion; };
		int get_accurany() const noexcept { return accuracy; };



		/********************************************************/
		/*						Сеттеры							*/
		/********************************************************/

		/* Изменение стандартных хар-к существа: при попытке установки текущих хар-к на значение,
		превышающее максимальное, состояние устанавливается на максимальное значение.
		   В случае установки максимального значения на то, которое меньше текущего, текущее значение
		меняется на максимальное
			Текущие хар-ки существа менять просто так нельзя; они по дефолту
		до введения его на поле будут совпадать с максимальными */

		void set_x(int);
		void set_y(int);
		void set_HP(int);
		void set_TP(int);
		void set_maxHP(int);
		void set_maxTP(int);
		void set_sight(int);
		void set_evasion(int);
		void set_accuracy(int);

		/********************************************************/
		/*					Остальные методы					*/
		/********************************************************/

		/*
			Сохранение базовой информации о существе:
		'x'_'y'_'HP'_'maxHP'_'evasion'_'accuracy'_'TP'_'maxTP'_'sight'
		*/
		virtual std::ostream& save(std::ostream&) const noexcept;

		// Загрузка базовой информации о существе из входного/файлового потока
		virtual std::istream& load(std::istream&) noexcept;

		// Вывод базовой информации о существе (не для сохранения в файл)
		friend std::ostream& operator <<(std::ostream& os, const Creature& cr) noexcept { return cr.print(os); };

	};

}
#endif // !_CREATURE_H_



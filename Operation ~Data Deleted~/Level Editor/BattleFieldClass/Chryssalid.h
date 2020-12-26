#ifndef CHRYSSALID_H
#define CHRYSSALID_H



namespace XCom {

	// Для объявления attack
	class Operative;

	
	/*  
		Класс пришельца "Дикое существо": у криссалида нет ни инвентаря, ни оружия (атакуют только в ближнем бою),
	 но выделяются повышенной скоростью, уроном и уклонением
	*/
	class Chryssalid : public Creature {

		// Урон в ближнем бою
		int damage;
		// Разброс урона
		int scatter;

	protected:

		virtual std::ostream& print(std::ostream&) const noexcept override;

	public:

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		Chryssalid() : Creature(CREATUREID_CHRYSSALID, 5, 50, 8, 0), damage(20), scatter(10) {};

		// Виртуальный деструктор класса "Криссалид": ничего не делает, т.к. объект чисто статический
		virtual ~Chryssalid() {};

		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/

		int get_damage() const noexcept { return damage; };
		int get_scatter() const noexcept { return scatter; };

		/********************************************************/
		/*						Сеттеры							*/
		/********************************************************/

		Chryssalid& set_damage(int);
		Chryssalid& set_scatter(int);

		/********************************************************/
		/*					Остальные методы					*/
		/********************************************************/


		// Создание копии криссалида
		virtual Chryssalid* clone() const noexcept override { return new Chryssalid(*this); };

		/* 
			Атака клиссалида: может атаковать 8 клеток вокруг себя. Возвращается строка "результата" (попадание, нет) и сам результат. 
		Если было попадание, урон цели наносится здесь же, но уничтожение существа (если надо) происходит вне метода.

		*/
		std::pair<bool, std::string> attack(Operative*);

		/*
			Сохранение информациии о криссалиде: Creature::save+'damage'_'scatter'
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// Загрузка информации о криссалиде из входного/файлового потока
		virtual std::istream& load(std::istream&) noexcept override;

		// Вывод информации о криссалиде во входной поток
		friend std::ostream& operator << (std::ostream& os, const Chryssalid& ch) { return ch.print(os); };
		// Загрузка информации о криссалиде из входного/файлового потока
		friend std::istream& operator >>(std::istream& is, Chryssalid& ch) noexcept { return ch.load(is); };

	};

}
#endif CHRYSSALID_H

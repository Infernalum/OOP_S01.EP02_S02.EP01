#ifndef CHRYSSALID_H
#define CHRYSSALID_H



namespace XCom {

	// Класс пришельца "Дикое существо"
	/* У криссалида нет ни инвентаря, ни оружия (атакуют только в ближнем бою),
	 но выделяются повышенной скоростью, уроном и уклонением
	*/
	class Chryssalid : public Creature {

		// Урон в ближнем бою
		int damage;
		// Разброс урона
		int scatter;

	protected:
		virtual std::ostream& print(std::ostream&) const override;

	public:

		virtual const char name() const override { return marking; };

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		Chryssalid() : Creature(5, 50, 8, 0), damage(20), scatter(10) { marking = 'c'; };

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
		virtual Chryssalid* clone() const override { return new Chryssalid(*this); };

		// Атака клиссалида:может атаковать 8 клеток вокруг себя
		virtual int get_damage(Creature*) override;

		/*
	Сохранение информациии о криссалиде: Creature::save+'damage'_'scatter'
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// Загрузка информации о криссалиде из входного/файлового потока
		virtual std::istream& load(std::istream&) noexcept override;

		// Вывод информации о криссалиде во входной поток
		friend std::ostream& operator << (std::ostream& os, const Chryssalid& ch) { return ch.print(os); };

	};

}
#endif CHRYSSALID_H

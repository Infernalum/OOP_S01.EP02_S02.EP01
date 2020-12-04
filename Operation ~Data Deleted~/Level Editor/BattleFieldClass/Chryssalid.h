#ifndef CHRYSSALID_H
#define CHRYSSALID_H



namespace Battlefield {

	// Класс "Дикое существо" (Пришелец)
	/* У криссалида нет ни инвентаря, ни оружия (атакуют только в ближнем бою),
	 но выделяются повышенной скоростью, уроном и уклонением
	*/
	class Chryssalid : public Creature {
	private:
		int damage;			// Урон в ближнем бою

	protected:
		virtual std::ostream& print(std::ostream&) const;

	public:

		virtual const char name() const { return marking; };

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		Chryssalid(int d = 1) : Creature(5, 50, 8), damage(d) { set_accuracy(100); };


		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/

		int get_damage() { return damage; };


		/********************************************************/
		/*						Сеттеры							*/
		/********************************************************/

		virtual Chryssalid& set_damage(int);


		virtual Chryssalid* clone() const { return new Chryssalid(*this); };

		/********************************************************/
		/*					Остальные методы					*/
		/********************************************************/



		friend std::ostream& operator << (std::ostream& os, const Chryssalid& ch) { return ch.print(os); };

	};

}
#endif CHRYSSALID_H

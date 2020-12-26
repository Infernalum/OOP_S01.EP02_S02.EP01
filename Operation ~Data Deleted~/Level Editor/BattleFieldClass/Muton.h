#ifndef MUTON_H 
#define MUTON_H

namespace XCom {


	/*!
	\brief Класс пришельца "Размуное существо"

	Является производным классом базового абстрактного класса "Существо"; не имеет инвентаря, но может держать в руках оружие, выкидывать его и подбирать новое
	*/
	class Muton : public Creature {

		// Активное оружие
		Weapon* hand;

	protected:

		virtual std::ostream& print(std::ostream&) const noexcept override;

	public:

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		Muton(Weapon* wp = nullptr) noexcept : Creature(CREATUREID_MUTON, 5, 50, 8, 20), hand(wp) {};

		// Виртуальный деструктор класса существа "Разумное существо"
		virtual ~Muton() {};

		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/

		// Получение константного указателя на оружие в руке
		const Weapon* get_hand() const noexcept { return hand; };


		/********************************************************/
		/*					Остальные методы					*/
		/********************************************************/


		// Выбросить/подобрать оружие (в качестве результата возвращается указатель на выброшенное оружие)
		Weapon* change_weapon(Weapon*) noexcept;

		// Создание копии разумного существа
		virtual Muton* clone() const noexcept override { return new Muton(*this); };

		/*
	Сохранение информациии о разумном существе: Creature::save + hand
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// Загрузка информации о разумном существе из входного/файлового потока
		virtual std::istream& load(std::istream&) noexcept override;

		// Вывод информации о разумном существе во входной поток
		friend std::ostream& operator << (std::ostream& os, const Muton& por) { return por.print(os); };
		// Загрузка информации о разумном существе из входного/файлового потока
		friend std::istream& operator >>(std::istream& is, Muton& mut) noexcept { return mut.load(is); };


	};

}

#endif // !MUTON_H 




#ifndef PORTER_H
#define PORTER_H

namespace XCom {

	// Класс пришельца "Фуражир": не может атаковать, но быстро и ловко передвигается и п*здит вещи везде, где можно
	class Porter :public Creature{
		mystd::Table<Item*> items;

	protected:
		virtual std::ostream& print(std::ostream&) const override;

	public:

		virtual const char name() const override { return marking; };


		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		Porter() : Creature(5, 50, 8, 20), items() { marking = 'p'; };

		// ???
		virtual ~Porter();

		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/

		mystd::Table<Item*>& access_to_table() { return items; };


		/********************************************************/
		/*					Остальные методы					*/
		/********************************************************/

		// Создание копии носильщика
		virtual Porter* clone() const override { return new Porter(*this); };

		// Атака носильщика: невозможно
		virtual int get_damage(Creature*) override { throw std::invalid_argument("Носильщики атаковать не могут; у них лапки, и они хотят больше золота!"); };

		/*
	Сохранение информациии о носильщике: Creature::save + items.size() + предметы
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// Загрузка информации о носильщике из входного/файлового потока
		virtual std::istream& load(std::istream&) noexcept override;

		// Вывод информации о носильщике во входной поток
		friend std::ostream& operator << (std::ostream& os, const Porter& por) { return por.print(os); };


	};

}


#endif // !PORTAER_H




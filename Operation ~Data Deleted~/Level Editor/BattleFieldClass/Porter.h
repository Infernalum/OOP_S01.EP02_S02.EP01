#ifndef PORTER_H
#define PORTER_H

namespace XCom {

	// Класс пришельца "Фуражир": не может атаковать, но быстро и ловко передвигается и п*здит вещи везде, где можно
	class Porter : public Creature {

		// Инвентарь Фуражира
		mystd::Table<Item*> inventory;

		// Клетки которые являются складскими точками. Т.к. пока пришельцы действуют по одиночке, у каждого свои знания об этих точках
		std::vector<std::pair<int, int>> starages;

	protected:

		virtual std::ostream& print(std::ostream&) const noexcept override;

	public:

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		Porter() : Creature(CREATUREID_PORTER, 5, 50, 8, 20), inventory(), starages() {};

		// Копирующий конструктор
		Porter(const Porter& copy) noexcept : inventory(copy.inventory), starages(copy.starages) {};

		// Копирующий оператор присваивания
		Porter& operator =(const Porter&) noexcept;

		// Перемещающий конструктор (Т.к. и для шаблона, и для вектора предусмотрена семантика перемещения)
		Porter(Porter&& move) noexcept : inventory(std::move(move.inventory)), starages(std::move(move.starages)) {};
		
		// Перемещающий оператор присваивания
		Porter& operator =(Porter&&) noexcept;


		// Виртуальый деструктор класса существа "Фуражир"
		virtual ~Porter() {};

		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/


		// Получение кол-ва вещей в инвентаре
		int size() const noexcept { return inventory.size(); };

		// Получение суммарного веса инвентаря
		double total_weight() const noexcept;

		// Вывод всего инвентаря
		std::ostream& show_table(std::ostream&) const noexcept;

		/********************************************************/
		/*					Остальные методы					*/
		/********************************************************/

		// Добавить новый предмет в инвентарь
		Porter& add_item(Item* item) noexcept { inventory.push_back(item); return *this; };

		// Выбросить (НЕ УДАЛИТЬ) предмет из инвентаря (принимается НОМЕР предмета)
		Item* drop_item(int);

		// Обратиться к какому-либо предмету по номеру
		Item* select_item(int);


		// Создание копии фуражира
		virtual Porter* clone() const noexcept override { return new Porter(*this); };

		/*
	Сохранение информациии о фуражире: Creature::save + inventory.size() + предметы
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// Загрузка информации о фуражире из входного/файлового потока
		virtual std::istream& load(std::istream&) noexcept override;

		// Вывод информации о фуражире во входной поток
		friend std::ostream& operator << (std::ostream& os, const Porter& por) { return por.print(os); };
		// Загрузка информации о фуражире из входного/файлового потока
		friend std::istream& operator >>(std::istream& is, Porter& por) noexcept { return por.load(is); };

	};

}


#endif // !PORTAER_H




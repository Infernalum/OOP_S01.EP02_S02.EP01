#ifndef TABLE_H
#define TABLE_H

namespace XCom {

	// Класс таблицы инвентаря персонажа (или клетки)
	class Table {
	private:
		std::map<int, Item*> elem;
	public:

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		// Пустой конструктор
		Table(): elem() {};

		// Копирующий конструктор
		Table(const Table&);
		
		// Копирующее присваивание
		Table& operator =(const Table&);
		
		// Деструктор
		~Table();

		/********************************************************/
		/*					 Класс-Итератор						*/
		/********************************************************/

		// Класс-итератор для таблицы
		friend class ConstTableIt;
		typedef ConstTableIt Const_Iterator;

		// Найти первый свободный номер (от 1 и до конца)


		// Вернуть итератор на элемент с данным номером
		Const_Iterator find(int) const;


		// Вернуть итератор на начало таблицы
		Const_Iterator begin() const;

		// Вернуть итератор за таблицу
		Const_Iterator end() const;

	};

}
#endif // !MYTABLE_H




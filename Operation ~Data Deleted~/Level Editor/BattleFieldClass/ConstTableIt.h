#ifndef CONSTTABLEIT_H
#define CONSTTABLEIT_H

namespace XCom {

	// Класс константного итератора для вывода и поиска элементов таблицы
	class ConstTableIt {
	private:
		std::map<int, Item*>::const_iterator cur;
	public:

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		ConstTableIt() : cur() {};
		ConstTableIt(std::map<int, Item*>::iterator it) : cur(it) {};
		ConstTableIt(std::map<int, Item*>::const_iterator it) : cur(it) {};

		/********************************************************/
		/*				Операции с итератором					*/
		/********************************************************/

		bool operator == (const ConstTableIt&) const;
		bool operator != (const ConstTableIt&) const;

		const std::pair<int, Item*>& operator *();

		// Почему?
		const std::pair<const int, Item*>* operator ->();

		// Инкремент
		ConstTableIt& operator ++();
		
		// Декримент
		ConstTableIt& operator ++(int);

	};
}

#endif // !CONSTMYTABLEIT_H




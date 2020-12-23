#ifndef TABLE_H
#define TABLE_H

//#include "pch.h"

namespace mystd {

	template<typename T>
	class TableIt;

	template<typename T>
	class ConstTableIt;

	// Шаблонный класс "Таблица", реализованная динамический массив
	template<typename T>
	class Table {

	private:
		static const int QUOTA = 5;			// Размер, на который увеличивать массив при переполнении
		int m_size;							// Максимальный размер таблицы
		int m_top;							// Текущее кол-во элементов таблицы
		T* m_data;							// Сам контейнер

		template <typename T>
		friend class TableIt;				// Класс-итератор

		template <typename T>
		friend class ConstTableIt;			// Константный класс-итератор
	public:

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		// Пустой конструктор
		Table() noexcept : m_size(QUOTA), m_top(0), m_data() {};

		// Конструктор с выделением памяти под sz элементов
		explicit Table(int sz) noexcept : m_size(sz), m_top(0), m_data(new T[m_size]) {};

		/*
			Конструктор через список инициализации
			Для его корректной работы должно быть выполнено хотя бы одно из следующих условий:
			- перегрузка оператора присваивания;
			- корректное глубокое копирование для оператора присваивания;
			- наличие explicit констурктора, чтобы он не мог использоваться для неявных преобразований;
		*/
		Table(const std::initializer_list<T>& list);

		// Деструктор
		~Table() { delete[] m_data; };

		// Копирующий конструктор
		Table(const Table&) noexcept;

		// Перемещающий конструктор
		Table(Table&&) noexcept;


		/********************************************************/
		/*					 Класс-итератор						*/
		/********************************************************/

		typedef TableIt<T> iterator;

		typedef ConstTableIt<T> const_iterator;

		iterator begin() { return iterator(m_data); };

		const_iterator begin() const { return const_iterator(m_data); };

		iterator end() { return iterator(m_data + m_top); };

		const_iterator end() const { return const_iterator(m_data + m_top); };




		/********************************************************/
		/*						Операторы						*/
		/********************************************************/

		// Копирующий оператор присваивания
		Table& operator =(const Table&);

		// Перемещающий оператор присваивания
		Table& operator =(Table&&) noexcept;

		// Оператор индексации 
		T& operator[](const int pos) { return m_data[pos]; };

		// Константный оператор индексации (r_value)
		const T& operator[](const int pos) const noexcept { return m_data[pos]; };



		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/

		// Вернуть длину таблицы
		int size() const noexcept { return m_top; };

		// Вернуть ёмкость таблицы
		int capicity() const noexcept { return m_size; };

		// Доступ к элементу с проверкой выхода за границу
		const T& at(const int) const;

		// Доступ к первому элементу таблицы. При пустой таблице ub
		const T& front() const noexcept { return m_data[0]; };

		// Доступ к последнему элементу таблицы. Вызов back к пустой таблице вызывает ub
		const T& back() const noexcept { return m_data[m_top - 1]; };

		// Проверка таблицы на пустоту: true, если пуста, false иначе
		bool empty() const { return !m_top; };



		/********************************************************/
		/*						Cеттеры							*/
		/********************************************************/

		// Доступ к элементу с проверкой выхода за границу
		T& at(const int);

		// Доступ к первому элементу таблицы. При пустой таблице поведение не определено
		T& front() noexcept { return m_data[0]; };

		// Доступ к последнему элементу таблицы. Вызов back в пустой таблице неопределен
		T& back() noexcept { return m_data[m_top - 1]; };

		// Очистить таблицу
		Table& clear();

		// Добавить элемент в таблицу
		iterator insert(iterator, const T&);

		// Вставка элемента в конец таблицы
		Table& push_back(const T&);

		// Удалить элемент таблицы через итератор: на место удаляемого элемента становится последний
		iterator erase(iterator);

		// Удалить последний элемент таблицы
		Table& pop_back();

		// Изменить длину таблицы
		Table& resize(const int);

		// Изменить ёмкость таблицы (зарезервировать место)
		Table& reserve(const int) noexcept;

		// Обменять содержимое двух векторов
		Table& swap(Table&) noexcept;

	};


	// Класс-иитератор для удобства доступа к таблице
	template<typename T>
	class TableIt {

		friend ConstTableIt<T>;

		T* m_ptr;

	public:

		TableIt() noexcept : m_ptr() {};

		TableIt(T* ob) noexcept : m_ptr(ob) {};

		// Присваивание
		TableIt& operator =(const TableIt& copy) noexcept { m_ptr = copy.m_ptr; return *this; };

		// "Указательное" сложение
		TableIt operator +(const int) const noexcept;

		// "Указательное" вычитание
		TableIt operator -(const int) const noexcept;

		// "Указательное" модифицирующее сложение
		TableIt& operator +=(const int pos) noexcept { m_ptr += pos; return *this; };

		// "Указательное" модифицирующее вычитание
		TableIt& operator -=(const int pos) noexcept { m_ptr -= pos; return *this; };

		// Инкремент
		TableIt& operator ++() noexcept;

		// Инкремент
		TableIt& operator --() noexcept;

		// Декремент
		TableIt operator++(int) noexcept;

		// Декремент
		TableIt operator--(int) noexcept;

		// Сравнение 
		bool operator <(const TableIt& cur) { return m_ptr < cur.m_ptr; };

		// Сравнение 
		bool operator <(const ConstTableIt<T>& cur) { return m_ptr < cur.m_ptr; };

		// Сранение 
		bool operator >(const TableIt& cur) { return m_ptr > cur.m_ptr; };

		// Сравнение
		bool operator >(const ConstTableIt<T>& cur) { return m_ptr > cur.m_ptr; };

		// Сравнение
		bool operator <=(const TableIt& cur) { return m_ptr <= cur.m_ptr; };

		// Сравнение
		bool operator <=(const ConstTableIt<T>& cur) { return m_ptr <= cur.m_ptr; };

		// Сравнение
		bool operator >=(const TableIt& cur) { return m_ptr >= cur.m_ptr; };

		// Сравнение
		bool operator >=(const ConstTableIt<T>& cur) { return m_ptr >= cur.m_ptr; };

		T& operator*() noexcept { return *m_ptr; };
		T& operator->() noexcept { return *m_ptr; };

		bool operator == (const TableIt& cur) const noexcept { return m_ptr == cur.m_ptr; };
		bool operator != (const TableIt& cur) const noexcept { return m_ptr != cur.m_ptr; };
		bool operator !() const noexcept { return !m_ptr; };

	};


	// Константный класс-итератор
	template<typename T>
	class ConstTableIt {


		friend TableIt<T>;

		const T* m_ptr;
	public:

		ConstTableIt() noexcept : m_ptr() {};

		ConstTableIt(const T* ob) noexcept : m_ptr(ob) {};

		// Присваивание
		ConstTableIt& operator =(const ConstTableIt& copy) noexcept { m_ptr = copy.m_ptr; return *this; };

		// "Указательное" сложение
		ConstTableIt operator +(const int) const noexcept;

		// "Указательное" вычитание
		ConstTableIt operator -(const int) const noexcept;

		// Инкремент
		ConstTableIt& operator ++() noexcept;

		// Инкремент
		ConstTableIt& operator --() noexcept;

		// Декремент
		ConstTableIt operator++(int) noexcept;

		// Декремент
		ConstTableIt operator--(int) noexcept;

		// Сравнение 
		bool operator <(const TableIt<T>& cur) { return m_ptr < cur.m_ptr; };

		// Сравнение 
		bool operator <(const ConstTableIt& cur) { return m_ptr < cur.m_ptr; };

		// Сранение 
		bool operator >(const TableIt<T>& cur) { return m_ptr > cur.m_ptr; };

		// Сравнение
		bool operator >(const ConstTableIt& cur) { return m_ptr > cur.m_ptr; };

		// Сравнение
		bool operator <=(const TableIt<T>& cur) { return m_ptr <= cur.m_ptr; };

		// Сравнение
		bool operator <=(const ConstTableIt& cur) { return m_ptr <= cur.m_ptr; };

		// Сравнение
		bool operator >=(const TableIt<T>& cur) { return m_ptr >= cur.m_ptr; };

		// Сравнение
		bool operator >=(const ConstTableIt& cur) { return m_ptr >= cur.m_ptr; };

		const T& operator*() const noexcept { return *m_ptr; };
		const T& operator->() const noexcept { return *m_ptr; };

		bool operator == (const ConstTableIt& cur) const noexcept { return m_ptr == cur.m_ptr; };
		bool operator != (const ConstTableIt& cur) const noexcept { return m_ptr != cur.m_ptr; };
		bool operator !() const noexcept { return !m_ptr; };

	};


}


namespace mystd {


	/********************************************************/
	/*					 Конструкторы						*/
	/********************************************************/


	// Используем делегирование конструкторов для создания начального массива, в который будет выполняться копирование элементов
	// Конструктор через список инициализации
	template<typename T> // метод, определенный вне тела класса, нуждается в собственном определении шаблона метода
	Table<T>::Table(const std::initializer_list<T>& list) : Table<T>(list.size() + QUOTA) {
		int cnt = 0;
		for (auto& element : list)
			m_data[cnt++] = element;
		m_top = list.size();
	}


	template <typename T>
	// Копирующий конструктор
	Table<T>::Table(const Table<T>& copy) noexcept : Table<T>(copy.m_size) {
		m_top = copy.m_top;
		for (int i = 0; i < m_top; ++i)
			m_data[i] = copy.m_data[i];
	}


	template<typename T>
	// Перемещающий конструктор
	Table<T>::Table(Table<T>&& move) noexcept : m_data(move.m_data), m_size(move.m_size), m_top(move.m_top) {
		move.m_data = nullptr;
	}


	/********************************************************/
	/*						Операторы						*/
	/********************************************************/


	template<typename T>
	// Копирующий оператор присваивания
	Table<T>& Table<T>::operator=(const Table<T>& copy) {
		if (this != &copy) {
			T* _new = new T[copy.m_size];
			m_size = copy.m_size;
			m_top = copy.m_top;
			delete[] m_data;
			m_data = _new;
			for (int i = 0; i < m_top; ++i)
				m_data[i] = copy.m_data[i];
		}
		return *this;
	}


	template<typename T>
	// Перемещающий оператор присваивания
	Table<T>& Table<T>::operator=(Table<T>&& move) noexcept {
		return swap(move);
	}


	/********************************************************/
	/*						Геттеры							*/
	/********************************************************/


	template<typename T>
	// Доступ к элементу с проверкой выхода за границу
	T& Table<T>::at(const int pos) {
		if (pos < 0 || pos > m_top)
			throw std::out_of_range("Неверный индикс таблицы. Попробуйте еще раз.");
		return m_data[pos];
	}


	template<typename T>
	// Доступ к элементу с проверкой выхода за границу
	const T& Table<T>::at(const int pos) const {
		if (pos < 0 || pos > m_top)
			throw std::out_of_range("Неверный индикс таблицы. Попробуйте еще раз.");
		return m_data[pos];
	}


	/********************************************************/
	/*						Cеттеры							*/
	/********************************************************/


	template <typename T>
	// Очистить таблицу
	Table<T>& Table<T>::clear() {
		T* _new = new T[QUOTA];
		m_size = QUOTA;
		m_top = 0;
		delete[] m_data;
		m_data = _new;
		return *this;
	}


	template<typename T>
	// Добавить элемент в таблицу
	TableIt<T> Table<T>::insert(TableIt<T> pos, const T& el) {
		if (m_top >= m_size) {
			T* _new = new T[m_size + QUOTA];
			m_size += QUOTA;
			T* _old = m_data;
			int i = 0;
			for (auto iter = begin(); iter != pos; ++iter)
				_new[i++] = *iter;
			_new[i++] = el;
			for (auto iter = pos + 1; iter != end(); ++iter)
				_new[i++] = *iter;
			m_data = _new;
			delete _old;
		}
		else {
			for (auto iter = end(); iter != pos; --iter)
				*iter = *(iter - 1);
			*pos = el;
		}
		++m_top;
		return pos;
	}


	template<typename T>
	// Добавить элемент в конец таблицы
	Table<T>& Table<T>::push_back(const T& el) {
		if (m_top >= m_size) {
			T* _new = new T[m_size + QUOTA];
			m_size += QUOTA;
			T* _old = m_data;
			m_data = _new;
			for (int i = 0; i < m_top; ++i)
				m_data[i] = _old[i];
			delete _old;
		}
		m_data[m_top++] = el;
		return *this;
	}


	template<typename T>
	// Удалить элемент из таблицы через итератор: на место удаляемого элемента становится последний
	TableIt<T> Table<T>::erase(TableIt<T> pos) {
		if (pos < begin() || pos >= end())
			throw std::out_of_range("Элемент не найден. Попробуйте еще раз.");
		if (m_top != 1) {
			pos = end() - 1;
		}
		--m_top;
		return pos;
	}


	template<typename T>
	// Удалить последний элемент таблицы
	Table<T>& Table<T>::pop_back() {
		if (m_top)
			--m_top;
		return *this;
	}


	template<typename T>
	// Изменить длину таблицы
	Table<T>& Table<T>::resize(const int newSize) {
		if (newSize < 0 || newSize > m_size)
			throw std::invalid_argument("Неверный размер. Попробуйте еще раз.");
		if (newSize > m_top)
			for (int i = m_top; i < newSize; ++i)
				m_data[i] = T();
		m_top = newSize;
		return *this;
	}

	template<typename T>
	// Изменить ёмкость таблицы (зарезервировать место)
	Table<T>& Table<T>::reserve(const int volume) noexcept {
		if (volume > m_size) {
			T* _new = new T[volume];
			T* _old = m_data;
			m_size = volume;
			m_data = _new;
			for (int i = 0; i < m_top; ++i)
				m_data[i] = _old[i];
			delete[] _old;
		}
		return *this;
	}


	template<typename T>
	// Обменять содержимое двух векторов
	Table<T>& Table<T>::swap(Table& other) noexcept {
		int tmp = m_top;
		m_top = other.m_top;
		other.m_top = tmp;
		tmp = m_size;
		m_size = other.m_size;
		other.m_size = tmp;
		T* ptr = m_data;
		m_data = other.m_data;
		other.m_data = ptr;
		return *this;
	}


	/********************************************************/
	/*					 Класс-итератор						*/
	/********************************************************/


	template<typename T>
	// "Указательное" сложение
	TableIt<T> TableIt<T>::operator +(const int pos) const noexcept {
		TableIt<T> res(m_ptr + pos);
		return res;
	}


	template<typename T>
	// "Указательное" вычитание
	TableIt<T> TableIt<T>::operator -(const int pos) const noexcept {
		TableIt<T> res(m_ptr - pos);
		return res;
	}


	// Инкремент
	template <typename T>
	TableIt<T>& TableIt<T>::operator++() noexcept {
		++m_ptr;
		return *this;
	}


	// Инкремент
	template <typename T>
	TableIt<T>& TableIt<T>::operator--() noexcept {
		--m_ptr;
		return *this;
	}


	// Декремент
	template<typename T>
	TableIt<T> TableIt<T>::operator++(int) noexcept {
		TableIt iter(*this);
		++m_ptr;
		return iter;
	}


	// Декремент
	template<typename T>
	TableIt<T> TableIt<T>::operator--(int) noexcept {
		TableIt iter(*this);
		--m_ptr;
		return iter;
	}

	template<typename T>
	// "Указательное" сложение
	ConstTableIt<T> ConstTableIt<T>::operator +(const int pos) const noexcept {
		ConstTableIt<T> res(m_ptr + pos);
		return res;
	}


	template<typename T>
	// "Указательное" вычитание
	ConstTableIt<T> ConstTableIt<T>::operator -(const int pos) const noexcept {
		ConstTableIt<T> res(m_ptr - pos);
		return res;
	}


	// Инкремент
	template <typename T>
	ConstTableIt<T>& ConstTableIt<T>::operator++() noexcept {
		++m_ptr;
		return *this;
	}


	// Инкремент
	template <typename T>
	ConstTableIt<T>& ConstTableIt<T>::operator--() noexcept {
		--m_ptr;
		return *this;
	}


	// Декремент
	template<typename T>
	ConstTableIt<T> ConstTableIt<T>::operator++(int) noexcept {
		ConstTableIt iter(*this);
		++m_ptr;
		return iter;
	}


	// Декремент
	template<typename T>
	ConstTableIt<T> ConstTableIt<T>::operator--(int) noexcept {
		ConstTableIt iter(*this);
		--m_ptr;
		return iter;
	}


}


#endif TABLE_H

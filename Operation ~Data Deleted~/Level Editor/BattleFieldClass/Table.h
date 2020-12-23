#ifndef TABLE_H
#define TABLE_H

//#include "pch.h"

namespace mystd {

	template<typename T>
	class TableIt;

	template<typename T>
	class ConstTableIt;

	// ��������� ����� "�������", ������������� ������������ ������
	template<typename T>
	class Table {

	private:
		static const int QUOTA = 5;			// ������, �� ������� ����������� ������ ��� ������������
		int m_size;							// ������������ ������ �������
		int m_top;							// ������� ���-�� ��������� �������
		T* m_data;							// ��� ���������

		template <typename T>
		friend class TableIt;				// �����-��������

		template <typename T>
		friend class ConstTableIt;			// ����������� �����-��������
	public:

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		// ������ �����������
		Table() noexcept : m_size(QUOTA), m_top(0), m_data() {};

		// ����������� � ���������� ������ ��� sz ���������
		explicit Table(int sz) noexcept : m_size(sz), m_top(0), m_data(new T[m_size]) {};

		/*
			����������� ����� ������ �������������
			��� ��� ���������� ������ ������ ���� ��������� ���� �� ���� �� ��������� �������:
			- ���������� ��������� ������������;
			- ���������� �������� ����������� ��� ��������� ������������;
			- ������� explicit ������������, ����� �� �� ��� �������������� ��� ������� ��������������;
		*/
		Table(const std::initializer_list<T>& list);

		// ����������
		~Table() { delete[] m_data; };

		// ���������� �����������
		Table(const Table&) noexcept;

		// ������������ �����������
		Table(Table&&) noexcept;


		/********************************************************/
		/*					 �����-��������						*/
		/********************************************************/

		typedef TableIt<T> iterator;

		typedef ConstTableIt<T> const_iterator;

		iterator begin() { return iterator(m_data); };

		const_iterator begin() const { return const_iterator(m_data); };

		iterator end() { return iterator(m_data + m_top); };

		const_iterator end() const { return const_iterator(m_data + m_top); };




		/********************************************************/
		/*						���������						*/
		/********************************************************/

		// ���������� �������� ������������
		Table& operator =(const Table&);

		// ������������ �������� ������������
		Table& operator =(Table&&) noexcept;

		// �������� ���������� 
		T& operator[](const int pos) { return m_data[pos]; };

		// ����������� �������� ���������� (r_value)
		const T& operator[](const int pos) const noexcept { return m_data[pos]; };



		/********************************************************/
		/*						�������							*/
		/********************************************************/

		// ������� ����� �������
		int size() const noexcept { return m_top; };

		// ������� ������� �������
		int capicity() const noexcept { return m_size; };

		// ������ � �������� � ��������� ������ �� �������
		const T& at(const int) const;

		// ������ � ������� �������� �������. ��� ������ ������� ub
		const T& front() const noexcept { return m_data[0]; };

		// ������ � ���������� �������� �������. ����� back � ������ ������� �������� ub
		const T& back() const noexcept { return m_data[m_top - 1]; };

		// �������� ������� �� �������: true, ���� �����, false �����
		bool empty() const { return !m_top; };



		/********************************************************/
		/*						C������							*/
		/********************************************************/

		// ������ � �������� � ��������� ������ �� �������
		T& at(const int);

		// ������ � ������� �������� �������. ��� ������ ������� ��������� �� ����������
		T& front() noexcept { return m_data[0]; };

		// ������ � ���������� �������� �������. ����� back � ������ ������� �����������
		T& back() noexcept { return m_data[m_top - 1]; };

		// �������� �������
		Table& clear();

		// �������� ������� � �������
		iterator insert(iterator, const T&);

		// ������� �������� � ����� �������
		Table& push_back(const T&);

		// ������� ������� ������� ����� ��������: �� ����� ���������� �������� ���������� ���������
		iterator erase(iterator);

		// ������� ��������� ������� �������
		Table& pop_back();

		// �������� ����� �������
		Table& resize(const int);

		// �������� ������� ������� (��������������� �����)
		Table& reserve(const int) noexcept;

		// �������� ���������� ���� ��������
		Table& swap(Table&) noexcept;

	};


	// �����-��������� ��� �������� ������� � �������
	template<typename T>
	class TableIt {

		friend ConstTableIt<T>;

		T* m_ptr;

	public:

		TableIt() noexcept : m_ptr() {};

		TableIt(T* ob) noexcept : m_ptr(ob) {};

		// ������������
		TableIt& operator =(const TableIt& copy) noexcept { m_ptr = copy.m_ptr; return *this; };

		// "������������" ��������
		TableIt operator +(const int) const noexcept;

		// "������������" ���������
		TableIt operator -(const int) const noexcept;

		// "������������" �������������� ��������
		TableIt& operator +=(const int pos) noexcept { m_ptr += pos; return *this; };

		// "������������" �������������� ���������
		TableIt& operator -=(const int pos) noexcept { m_ptr -= pos; return *this; };

		// ���������
		TableIt& operator ++() noexcept;

		// ���������
		TableIt& operator --() noexcept;

		// ���������
		TableIt operator++(int) noexcept;

		// ���������
		TableIt operator--(int) noexcept;

		// ��������� 
		bool operator <(const TableIt& cur) { return m_ptr < cur.m_ptr; };

		// ��������� 
		bool operator <(const ConstTableIt<T>& cur) { return m_ptr < cur.m_ptr; };

		// �������� 
		bool operator >(const TableIt& cur) { return m_ptr > cur.m_ptr; };

		// ���������
		bool operator >(const ConstTableIt<T>& cur) { return m_ptr > cur.m_ptr; };

		// ���������
		bool operator <=(const TableIt& cur) { return m_ptr <= cur.m_ptr; };

		// ���������
		bool operator <=(const ConstTableIt<T>& cur) { return m_ptr <= cur.m_ptr; };

		// ���������
		bool operator >=(const TableIt& cur) { return m_ptr >= cur.m_ptr; };

		// ���������
		bool operator >=(const ConstTableIt<T>& cur) { return m_ptr >= cur.m_ptr; };

		T& operator*() noexcept { return *m_ptr; };
		T& operator->() noexcept { return *m_ptr; };

		bool operator == (const TableIt& cur) const noexcept { return m_ptr == cur.m_ptr; };
		bool operator != (const TableIt& cur) const noexcept { return m_ptr != cur.m_ptr; };
		bool operator !() const noexcept { return !m_ptr; };

	};


	// ����������� �����-��������
	template<typename T>
	class ConstTableIt {


		friend TableIt<T>;

		const T* m_ptr;
	public:

		ConstTableIt() noexcept : m_ptr() {};

		ConstTableIt(const T* ob) noexcept : m_ptr(ob) {};

		// ������������
		ConstTableIt& operator =(const ConstTableIt& copy) noexcept { m_ptr = copy.m_ptr; return *this; };

		// "������������" ��������
		ConstTableIt operator +(const int) const noexcept;

		// "������������" ���������
		ConstTableIt operator -(const int) const noexcept;

		// ���������
		ConstTableIt& operator ++() noexcept;

		// ���������
		ConstTableIt& operator --() noexcept;

		// ���������
		ConstTableIt operator++(int) noexcept;

		// ���������
		ConstTableIt operator--(int) noexcept;

		// ��������� 
		bool operator <(const TableIt<T>& cur) { return m_ptr < cur.m_ptr; };

		// ��������� 
		bool operator <(const ConstTableIt& cur) { return m_ptr < cur.m_ptr; };

		// �������� 
		bool operator >(const TableIt<T>& cur) { return m_ptr > cur.m_ptr; };

		// ���������
		bool operator >(const ConstTableIt& cur) { return m_ptr > cur.m_ptr; };

		// ���������
		bool operator <=(const TableIt<T>& cur) { return m_ptr <= cur.m_ptr; };

		// ���������
		bool operator <=(const ConstTableIt& cur) { return m_ptr <= cur.m_ptr; };

		// ���������
		bool operator >=(const TableIt<T>& cur) { return m_ptr >= cur.m_ptr; };

		// ���������
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
	/*					 ������������						*/
	/********************************************************/


	// ���������� ������������� ������������� ��� �������� ���������� �������, � ������� ����� ����������� ����������� ���������
	// ����������� ����� ������ �������������
	template<typename T> // �����, ������������ ��� ���� ������, ��������� � ����������� ����������� ������� ������
	Table<T>::Table(const std::initializer_list<T>& list) : Table<T>(list.size() + QUOTA) {
		int cnt = 0;
		for (auto& element : list)
			m_data[cnt++] = element;
		m_top = list.size();
	}


	template <typename T>
	// ���������� �����������
	Table<T>::Table(const Table<T>& copy) noexcept : Table<T>(copy.m_size) {
		m_top = copy.m_top;
		for (int i = 0; i < m_top; ++i)
			m_data[i] = copy.m_data[i];
	}


	template<typename T>
	// ������������ �����������
	Table<T>::Table(Table<T>&& move) noexcept : m_data(move.m_data), m_size(move.m_size), m_top(move.m_top) {
		move.m_data = nullptr;
	}


	/********************************************************/
	/*						���������						*/
	/********************************************************/


	template<typename T>
	// ���������� �������� ������������
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
	// ������������ �������� ������������
	Table<T>& Table<T>::operator=(Table<T>&& move) noexcept {
		return swap(move);
	}


	/********************************************************/
	/*						�������							*/
	/********************************************************/


	template<typename T>
	// ������ � �������� � ��������� ������ �� �������
	T& Table<T>::at(const int pos) {
		if (pos < 0 || pos > m_top)
			throw std::out_of_range("�������� ������ �������. ���������� ��� ���.");
		return m_data[pos];
	}


	template<typename T>
	// ������ � �������� � ��������� ������ �� �������
	const T& Table<T>::at(const int pos) const {
		if (pos < 0 || pos > m_top)
			throw std::out_of_range("�������� ������ �������. ���������� ��� ���.");
		return m_data[pos];
	}


	/********************************************************/
	/*						C������							*/
	/********************************************************/


	template <typename T>
	// �������� �������
	Table<T>& Table<T>::clear() {
		T* _new = new T[QUOTA];
		m_size = QUOTA;
		m_top = 0;
		delete[] m_data;
		m_data = _new;
		return *this;
	}


	template<typename T>
	// �������� ������� � �������
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
	// �������� ������� � ����� �������
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
	// ������� ������� �� ������� ����� ��������: �� ����� ���������� �������� ���������� ���������
	TableIt<T> Table<T>::erase(TableIt<T> pos) {
		if (pos < begin() || pos >= end())
			throw std::out_of_range("������� �� ������. ���������� ��� ���.");
		if (m_top != 1) {
			pos = end() - 1;
		}
		--m_top;
		return pos;
	}


	template<typename T>
	// ������� ��������� ������� �������
	Table<T>& Table<T>::pop_back() {
		if (m_top)
			--m_top;
		return *this;
	}


	template<typename T>
	// �������� ����� �������
	Table<T>& Table<T>::resize(const int newSize) {
		if (newSize < 0 || newSize > m_size)
			throw std::invalid_argument("�������� ������. ���������� ��� ���.");
		if (newSize > m_top)
			for (int i = m_top; i < newSize; ++i)
				m_data[i] = T();
		m_top = newSize;
		return *this;
	}

	template<typename T>
	// �������� ������� ������� (��������������� �����)
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
	// �������� ���������� ���� ��������
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
	/*					 �����-��������						*/
	/********************************************************/


	template<typename T>
	// "������������" ��������
	TableIt<T> TableIt<T>::operator +(const int pos) const noexcept {
		TableIt<T> res(m_ptr + pos);
		return res;
	}


	template<typename T>
	// "������������" ���������
	TableIt<T> TableIt<T>::operator -(const int pos) const noexcept {
		TableIt<T> res(m_ptr - pos);
		return res;
	}


	// ���������
	template <typename T>
	TableIt<T>& TableIt<T>::operator++() noexcept {
		++m_ptr;
		return *this;
	}


	// ���������
	template <typename T>
	TableIt<T>& TableIt<T>::operator--() noexcept {
		--m_ptr;
		return *this;
	}


	// ���������
	template<typename T>
	TableIt<T> TableIt<T>::operator++(int) noexcept {
		TableIt iter(*this);
		++m_ptr;
		return iter;
	}


	// ���������
	template<typename T>
	TableIt<T> TableIt<T>::operator--(int) noexcept {
		TableIt iter(*this);
		--m_ptr;
		return iter;
	}

	template<typename T>
	// "������������" ��������
	ConstTableIt<T> ConstTableIt<T>::operator +(const int pos) const noexcept {
		ConstTableIt<T> res(m_ptr + pos);
		return res;
	}


	template<typename T>
	// "������������" ���������
	ConstTableIt<T> ConstTableIt<T>::operator -(const int pos) const noexcept {
		ConstTableIt<T> res(m_ptr - pos);
		return res;
	}


	// ���������
	template <typename T>
	ConstTableIt<T>& ConstTableIt<T>::operator++() noexcept {
		++m_ptr;
		return *this;
	}


	// ���������
	template <typename T>
	ConstTableIt<T>& ConstTableIt<T>::operator--() noexcept {
		--m_ptr;
		return *this;
	}


	// ���������
	template<typename T>
	ConstTableIt<T> ConstTableIt<T>::operator++(int) noexcept {
		ConstTableIt iter(*this);
		++m_ptr;
		return iter;
	}


	// ���������
	template<typename T>
	ConstTableIt<T> ConstTableIt<T>::operator--(int) noexcept {
		ConstTableIt iter(*this);
		--m_ptr;
		return iter;
	}


}


#endif TABLE_H

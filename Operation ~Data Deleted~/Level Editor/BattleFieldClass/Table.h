#ifndef TABLE_H
#define TABLE_H

namespace XCom {

	// ����� ������� ��������� ��������� (��� ������)
	class Table {
	private:
		std::map<int, Item*> elem;
	public:

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		// ������ �����������
		Table(): elem() {};

		// ���������� �����������
		Table(const Table&);
		
		// ���������� ������������
		Table& operator =(const Table&);
		
		// ����������
		~Table();

		/********************************************************/
		/*					 �����-��������						*/
		/********************************************************/

		// �����-�������� ��� �������
		friend class ConstTableIt;
		typedef ConstTableIt Const_Iterator;

		// ����� ������ ��������� ����� (�� 1 � �� �����)


		// ������� �������� �� ������� � ������ �������
		Const_Iterator find(int) const;


		// ������� �������� �� ������ �������
		Const_Iterator begin() const;

		// ������� �������� �� �������
		Const_Iterator end() const;

	};

}
#endif // !MYTABLE_H




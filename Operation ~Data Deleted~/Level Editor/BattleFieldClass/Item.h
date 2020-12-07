#ifndef ITEM_H
#define ITEM_H


namespace XCom {

	class Item {
	private:

		// ���-�� �����, ������� ����� ���������, ����� ������� ������� (����������, ����������, �������������� � ��)
		int usedPoint;

	protected:

		virtual std::ostream& print(std::ostream&) const;

		// �������� ������������ � protected �������, ����� ���������� ���� ����
		// �������� ������� ������� ������������ ������, �� ������ � ��� ����� �������� ������

		/* �������: ������� �� �������� ����������� ������� � ���� ������������� ��� ������������ ������� ������� */

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		// ����������/������������ ������������ �� ���������

		// ������������ �����������
		Item(int uP = 1);


		// ��� �������� (��������� ��������, �.�. ��� ������� � ���������� ����� (�� � ��� ������) ��� ������������� � ������ �������� �������� �������
		double weight;

	public:

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		double get_weight() { return weight; };
		int get_uP() { return usedPoint; };



		/********************************************************/
		/*						�������							*/
		/********************************************************/

		// ��������� ���� �������� (��� ������ ���� �������� ���� ����� �������� ����)
		virtual const Item& set_weight() = 0;

		/*
			������������� ���������.
		��� ���������� �����: �������� n �������� �� �����; � ������, ���� � ����� ������ ��������, ������������� ���-��, ������� ����� �������
		��� �������: ������������ ������� (����� ������������� ������� ���������)
		��� ������: ���������� 1-�� ��������. ����������� ���� ��������� ��� ���������� � n ������
		*/
		virtual int using_item(int) = 0;

		Item& set_usedPoint(int);

		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/


		// �������� ����� ��������
		Item* clone() { return this; };

		friend std::ostream& operator << (std::ostream& os, const Item& c) { return c.print(os); };

	};

}

#endif // !_ITEM_H_




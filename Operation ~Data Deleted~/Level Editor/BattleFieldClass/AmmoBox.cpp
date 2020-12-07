#include "pch.h"

namespace XCom {

	/********************************************************/
	/*					 ������������						*/
	/********************************************************/

	// �����������, ��������� ���� � 40 ��������� � �������� 2 TP �� �����������
	AmmoBox::AmmoBox(int up, double wof, int maxqty) : Item(up) {
		if (wof <= 0)
			throw std::invalid_argument("��� ������� ������ ���� �������������. ���������� ��� ���.");
		if (maxqty < 0)
			throw std::invalid_argument("���� �� ����� ����� ������������� ��������. ���������� ��� ���.");
		weightOfOne = wof;
		maxQty = maxqty;
		qty = maxqty;
		set_weight();
	}



	/********************************************************/
	/*						�������							*/
	/********************************************************/

	// �������� ����� �� �������
	bool AmmoBox::empty() {
		if (!qty)
			return true;
		else
			return false;
	}


	/********************************************************/
	/*						�������							*/
	/********************************************************/


	AmmoBox& AmmoBox::set_qty(int q) {
		if (q < 0)
			throw std::invalid_argument("���-�� �������� � ����� ������ ���� �������������. ���������� ��� ��.");
		if (q > maxQty)
			qty = maxQty;
		qty = q;
		set_weight();
		return *this;
	}


	AmmoBox& AmmoBox::set_max_qty(int mq) {
		if (mq < 0)
			throw std::invalid_argument("������������ ���-�� �������� �� ����� ���� �������������. ���������� ��� ���.");
		maxQty = mq;
		if (qty > maxQty) {
			qty = maxQty;
			set_weight();
		}
		return *this;
	}


	AmmoBox& AmmoBox::set_weight_of_one(double woo) {
		if (woo <= 0)
			throw std::invalid_argument("��� ������ ������� ������ ���� �������������. ���������� ��� ���.");
		weightOfOne = woo;
		set_weight();
		return *this;
	}


	// �������� ���� ����� � ���������
	const AmmoBox& AmmoBox::set_weight() {
		weight = weightOfOne * qty;
		return *this;
	}

	/********************************************************/
	/*					��������� ������					*/
	/********************************************************/


	// ������������� ��������: �������� count �������� �� �����. ���� � ����� ������ count ��������, �� �������������, ������� ����.
	int AmmoBox::using_item(int count) {
		if (count < 0)
			throw std::invalid_argument("���-�� ��������, ������� �� ������ ��������, ������ ���� �������������. ���������� ��� ���.");
		int res;
		if (qty < count) {
			res = qty;
			qty = 0;
		}
		else {
			res = count;
			qty -= count;
		}
		// ������������� ���
		set_weight();
		return res;
	}


	std::ostream& AmmoBox::print(std::ostream& os) const {
		os << "�������: �������; �������: " << qty << '\\' << maxQty << "; ���: " << weight << "; ";
		Item::print(os);
		return os;
	}

}

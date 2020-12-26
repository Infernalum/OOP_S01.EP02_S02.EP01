#include "pch.h"

namespace XCom {

	/********************************************************/
	/*					 ������������						*/
	/********************************************************/


	AmmoBox::AmmoBox(const Ammo& type, int up, int maxqty) : Item(ITEMID_AMMOBOX, up) {
		if (maxqty < 0)
			throw std::invalid_argument("���� �� ����� ����� ������������� ��������. ���������� ��� ���.");
		ammo = type;
		maxQty = maxqty;
		qty = maxqty;
		set_weight(0);
	}



	/********************************************************/
	/*						�������							*/
	/********************************************************/

	// �������� ����� �� �������
	bool AmmoBox::empty() const noexcept {
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
		set_weight(0);
		return *this;
	}


	AmmoBox& AmmoBox::set_maxQty(int mq) {
		if (mq < 0)
			throw std::invalid_argument("������������ ���-�� �������� �� ����� ���� �������������. ���������� ��� ���.");
		maxQty = mq;
		if (qty > maxQty) {
			qty = maxQty;
			set_weight(0);
		}
		return *this;
	}

	/********************************************************/
	/*					��������� ������					*/
	/********************************************************/


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
		set_weight(0);
		return res;
	}


	std::ostream& AmmoBox::print(std::ostream& os) const noexcept {
		os << "���� � ��������� (" << qty << '\\' << maxQty << "); ";
		Item::print(os);
		os << ammo;
		return os;
	}


	std::ostream& AmmoBox::save(std::ostream& os) const noexcept {
		Item::save(os) << qty << ' ' << maxQty << '\n';
		ammo.save(os);
		return os;
	}


	std::istream& AmmoBox::load(std::istream& is) noexcept {
		Item::load(is) >> qty;
		is.ignore() >> maxQty;
		is.ignore() >> ammo;
		return is;
	}
}

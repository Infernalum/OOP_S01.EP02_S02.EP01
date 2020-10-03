
#include<stdio.h>
#include<exception>
#include "Catenary.h"


namespace Class { /* ��� �������� ������������ ����? */

	// ������� �������� ������������ ��������� �������
	// �����, ��� ��� � ��������� �� ������� ���� ������� �� ����� ������������ ����� � ������������� ��������� 
	bool Point::check() const {
		if (y <= 0)
			return false;
		else
			return true;
	}

	// ���������������� ����������� ��� �������� �� ���������
	Catenary::Catenary(const Point& p, const Point& l_limit, const Point& r_limit) {
		if (!p.check())
			// ����� ���������� ����������� ����������
			throw std::exception("�������� ������� ����� ���� ������ �������������. ���������� ��� ���: ");
		Catenary::p = p;
		if (l_limit.x <= r_limit.x) {
			// ����� ����� ��������� this
			this->l_limit = l_limit;
			this->r_limit = r_limit;
		}
		else {
			// � ����� ����� ���������� ���������
			Catenary::l_limit = r_limit;
			Catenary::r_limit = l_limit;
		}
	}

	Catenary& Catenary::setL(const Point& l_limit, const Point& r_limit) {
		if (l_limit.x <= r_limit.x) {
			// ����� ����� ��������� this
			this->l_limit = l_limit;
			this->r_limit = r_limit;
		}
		else {
			// � ����� ����� ���������� ���������
			Catenary::l_limit = r_limit;
			Catenary::r_limit = r_limit;
		}
		return *this;
	}

	// �.4: ����� ���� ������ ����� �� �� �������� �� ��� �������
	Type Catenary::length(const Point& p) const {
		return sqrt(pow(p.y, 2) - pow(Catenary::p.y, 2));
	}

	// �.5: ������ �������� ������ ����� �� �� �������� ������������ ���������� �� ��� �������
	Type Catenary::radius(const Point& p) const {
		return (pow(p.y, 2) / Catenary::p.y);
	}

	// �.6: ���������� ������ �������� ������ ����� � ��� ������������ ���������� �� ��� �������
	Point Catenary::center(const Point& p) const {
		Type ch = cosh(p.x / Catenary::p.y);
		Type sh = sinh(p.x / Catenary::p.y);
		Point res;
		res.x = Catenary::p.y * (ch * sh + log(ch - sh));
		res.y = 2 * Catenary::p.y * ch;
		return res;
	}

	// �.7: ������� ������������� ��������, ������������ ������ ������ � �� ��������� �� ��� �������
	Type Catenary::area() const {
		return (Catenary::p.y * (sqrt(pow(Catenary::l_limit.y, 2) - pow(Catenary::p.y, 2)) - (sqrt(pow(Catenary::r_limit.y, 2) - pow(Catenary::p.y, 2)))));
	}

}
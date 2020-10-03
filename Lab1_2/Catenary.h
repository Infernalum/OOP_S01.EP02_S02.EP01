// ����������� ������ "������ �����"

#ifndef _CATENARY_H_
#define _CATENARY_H_


#include<iostream>
#include <math.h>

typedef double Type;


namespace Class {


	// ���������� �������� �� ��������� �������� � ���������
	inline Type ordinate(const Type& x0, const Type& a) { return (a * (cosh(x0 / a))); }


	// ��������� ����� �� ���������
	struct Point {
		Type x, y;
		Point() : x(0), y(1) {};								// ������ �����������, ������� ������ ����� ������������ (0,1)
		Point(Type x0, Type y0) : x(x0), y(y0) {};				// ���������������� �����������, ������� �� ����������� ��������, ���� ������ �� ���������, � �������������� ���������� ��� ��������
		bool check() const;										// ������� �������� ������������ ��������� �������
	};


	// ����� "������ �����". �������� �������� ����. �������� ����� �������� ������� ������������ ������ ��������� �� Oy (�����������: > 0). 
	class Catenary {
	private:
		Point p;																// ���������� �������
		Point l_limit;															// ����� ������� ���� (�������� ��������, ����� ��������� ��������)
		Point r_limit;															// ������ ������� ���� (������� ����� ��� �.4, 7)
	public:
		Catenary() : p(0, 1), l_limit(0, 1), r_limit(0, 1) {};					// ������ �����������; �� ��������� ���������� ���� � �������� � ����� (0,1)
		Catenary(const Point& p, const Point& l_limit, const Point& r_limit);	// ���������������� ����������� (��� ��� ����. �������������) 
		// ������� - set'����
		Catenary& setP(const Point& p0) { p = p0; return *this; };				// ������ ��� ������� ������� ����
		Catenary& setL(const Point& l_limit, const Point& r_limit);				// ������ ��� ������� ������
		// ������� - get'���� (����� ��� ������������)
		// const ���������� ���, ��� ������� �������� �������������� ���������� � �� �������� ��������� �������
		Point getP() const { return p; };
		Point getL_limit() const { return l_limit; };
		Point getR_limit() const { return r_limit; };
		// ������ ������
		Type length(const Point&) const;							// �.4: ����� ���� ������ ����� �� �� �������� �� ��� �������
		Type radius(const Point&) const;							// �.5: ������ �������� ������ ����� �� �� �������� ������������ ���������� �� ��� �������
		Point center(const Point&) const;							// �.6: ���������� ������ �������� ������ ����� � ��� ������������ ���������� �� ��� �������
		Type area() const;											// �.7: ������� ������������� ��������, ������������ ������ ������ � �� ��������� �� ��� �������
		~Catenary() {};												// ���������� �� ���������
	};

}


#endif // !_CATENARY_H_




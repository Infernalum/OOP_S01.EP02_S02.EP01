#include "pch.h"
#include "Item.h"

namespace Battlefield {



	/********************************************************/
	/*						�������							*/
	/********************************************************/

	Item& Item::set_weight(int w) {
		if (w < 1)
			throw std::invalid_argument("��� �������� ������ ���� �������������. ���������� ��� ���.");
		weight = w;
		return *this;
	}

	Item& Item::set_usedPoint(int uP) {
		if (uP < 1)
			throw std::invalid_argument("���-�� ��������� ����� ������� ������ ���� �������������. ���������� ��� ���.");
		usedPoint = uP;
		return *this;
	}


}


#include "Catenary.h"
#include "Lab1_2.h"


extern const char* msgs[];

int(*fptr[])(Class::Catenary&) = { NULL, Lab1_2::D_SetPoint, Lab1_2::D_SetBorders, Lab1_2::D_GetOrdinate, Lab1_2::D_GetLength, Lab1_2::D_GetRadius, Lab1_2::D_GetCenter, Lab1_2::D_GetArea};

// В чем разница main, wmain и tmain:
//https://ru.stackoverflow.com/questions/213830/tmain-%D0%BF%D0%BE%D1%87%D0%B5%D0%BC%D1%83-%D1%82%D0%B0%D0%BA%D0%BE%D0%B5-%D0%BD%D0%B0%D0%B7%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5
int main() {
	Class::Point p, l, r;
	Class::Catenary x(p, l, r);
	Class::Catenary x2(p, l, r);
	int a;
	Lab1_2::getNum(a);
	int rc;
	while (rc = Lab1_2::dialog(msgs, NMsgs))
		if (!fptr[rc](x))
			break;
	return 0;
}
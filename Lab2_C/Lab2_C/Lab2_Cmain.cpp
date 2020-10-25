#include "Lab2_C.h"

extern const char* msgs[];

int (*fptr[])(CardDeckClass::CardDeck&) = { NULL, Lab2_A::D_GetDeck, Lab2_A::D_AddNewCard, Lab2_A::D_GetCurrentCard, Lab2_A::D_Sort, Lab2_A::D_ChooseSuit };

int main() {
	setlocale(0, "");
	std::cout << "Добро пожаловать в тестирующую программу для класса \"Карточная колода\" ";
	//CardDeckClass::CardDeck p1(10, 5);
	//std::cout << p1;
	//CardDeckClass::CardDeck p2(p1);
	//std::cout << p2;
	CardDeckClass::CardDeck deck = Lab2_A::Input();
	int rc;
	while (rc = Lab2_A::dialog(msgs, NMsgs))
		if (!fptr[rc](deck))
			break;
	return 0;
}
#include "Lab2_A.h"

extern const char* msgs[];

int (*fptr[])(CardDeckClass::CardDeck&) = { NULL, Lab2_A::D_GetDeck, Lab2_A::D_AddNewCard, Lab2_A::D_GetCurrentCard, Lab2_A::D_Sort, Lab2_A::D_ChooseSuit };

int main() {
	setlocale(0, "");
	std::cout << "Добро пожаловать в тестирующую программу для класса \"Карточная колода\". Пожалуйста, выберите способ создания вышей колоды: ==> ";
	CardDeckClass::CardDeck deck = Lab2_A::Input();
	int rc;
	while (rc = Lab2_A::dialog(msgs, NMsgs))
		if (!fptr[rc](deck))
			break;
	return 0;
}
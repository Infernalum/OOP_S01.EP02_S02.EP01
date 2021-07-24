#include <QCoreApplication>
#include "lab2_b.h"

extern const char* msgs[];

int (*fptr[])(CardDeckClass::CardDeck&) = {NULL,
                                           Lab2_B::D_GetDeck,
                                           Lab2_B::D_AddNewCard,
                                           Lab2_B::D_GetCurrentCard,
                                           Lab2_B::D_Sort,
                                           Lab2_B::D_ChooseSuit};

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);
  qtConsole(
      "Добро пожаловать в тестирующую программу для класса \"Карточная "
      "колода\". Пожалуйста, выберите способ создания вышей колоды: ==> ");
  CardDeckClass::CardDeck deck = Lab2_B::Input();
  int rc;
  while (rc = Lab2_B::dialog(msgs, NMsgs))
    if (!fptr[rc](deck))
      break;

  return a.exec();
}

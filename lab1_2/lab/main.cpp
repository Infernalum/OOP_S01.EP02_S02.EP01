
#include "lab1_2.h"

extern const char* msgs[];

int (*fptr[])(Class::Catenary&) = {NULL,
                                   Lab1_2::D_SetVertex,
                                   Lab1_2::D_SetBorders,
                                   Lab1_2::D_GetOrdinate,
                                   Lab1_2::D_GetLength,
                                   Lab1_2::D_GetRadius,
                                   Lab1_2::D_GetCenter,
                                   Lab1_2::D_GetArea};

int main() {
  qtConsole(
      "Добро пожаловать в тестировочную программу класса \"Цепная "
      "линия\". Пожалуйста, инициализируйте первичное состояние.\n");
  Class::Catenary line = Lab1_2::Input();
  int rc;
  while ((Lab1_2::D_GetStatus(line)) && (rc = Lab1_2::dialog(msgs, NMsgs)))
    if (!fptr[rc](line))
      break;
  return 0;
}

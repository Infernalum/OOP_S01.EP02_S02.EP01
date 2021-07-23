
#include "cetanerylib.h"
#include <stdio.h>
#include <stdexcept>

namespace Class { /* Как изменить пространство имен? */

// Функция проверки корректности введенной вершины
// Нужна, так как в программе по условию лабы априори не может существовать
// точки с отрицательной ординатой
bool Point::check() const {
  if (y <= 0)
    return false;
  else
    return true;
}

// Инициализирующий конструктор без значений по умолчанию
Catenary::Catenary(const Point& p0, Type x1, Type x2) {
  if (!p0.check())
    throw std::invalid_argument(
        "Сказано же : ордината строго положительна. Попробуйте еще раз.");
  p = p0;
  Catenary::setL(x1, x2);
}

// Сеттер для изменения границ
Catenary& Catenary::setL(Type x1, Type x2) {
  Type y1 = ordinate(x1);
  Type y2 = ordinate(x2);
  if (x1 <= x2) {
    // Можно через указатель this
    this->l_limit.x = x1;
    this->l_limit.y = y1;
    this->r_limit.x = x2;
    this->r_limit.y = y2;
  } else {
    // А можно через разрешение видимости
    Catenary::l_limit.x = x2;
    Catenary::l_limit.y = y2;
    Catenary::r_limit.x = x1;
    Catenary::r_limit.y = y1;
  }
  return *this;
}

// Сеттер для изменения вершины
void Catenary::setP(const Point& p0) {
  if (!p0.check())
    throw std::invalid_argument(
        "Сказано же : ордината строго положительна. Попробуйте еще раз.");
  p = p0;
  Catenary::setL(l_limit.x, r_limit.x);
}

// Возвращает значение ординаты по значению абсциссы
Type Catenary::ordinate(Type x) const {
  return (p.y * (cosh((x - p.x) / p.y)));
}

// п.4: длина дуги цепной линии от ее проекции на оси абсцисс
Type Catenary::length() const {
  Type l1 = p.y * cosh((l_limit.x - p.x) / p.y);
  Type l2 = p.y * cosh((r_limit.x - p.x) / p.y);
  if (((l_limit.x - p.x) * (r_limit.x - p.x)) <= 0)
    return (l1 + l2);
  else
    return abs(l1 - l2);
}

// п.5: радиус кривизны цепной линии относительно координаты по оси абсцисс
Type Catenary::radius(Type x) const {
  return (pow(ordinate(x), 2) / p.y);
}

// п.6: координаты центра кривизны цепной динии в ДСК относительно координаты по
// оси абсцисс
Point Catenary::center(Type x) const {
  Type ch = cosh(x / Catenary::p.y);
  Type sh = sinh(x / Catenary::p.y);
  Point res;
  res.x = Catenary::p.y * (ch * sh + log(ch - sh));
  res.y = 2 * Catenary::p.y * ch;
  return res;
}

// п.7: площадь криволинейной трапеции, образованной цепной линией и ее
// проекцией на ось абсцисс
Type Catenary::area() const {
  return (p.y * (sqrt(pow(l_limit.y, 2) - pow(p.y, 2)) -
                 (sqrt(pow(r_limit.y, 2) - pow(p.y, 2)))));
}

}  // namespace Class

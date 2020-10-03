
#include<stdio.h>
#include<exception>
#include "Catenary.h"


namespace Class { /* Как изменить пространство имен? */

	// Функция проверки корректности введенной вершины
	// Нужна, так как в программе по условию лабы априори не может существовать точки с отрицательной ординатой 
	bool Point::check() const {
		if (y <= 0)
			return false;
		else
			return true;
	}

	// Инициализирующий конструктор без значений по умолчанию
	Catenary::Catenary(const Point& p, const Point& l_limit, const Point& r_limit) {
		if (!p.check())
			// Класс исключения стандартной библиотеки
			throw std::exception("Ордината вершины может быть только положительной. Попробуйте еще раз: ");
		Catenary::p = p;
		if (l_limit.x <= r_limit.x) {
			// Можно через указатель this
			this->l_limit = l_limit;
			this->r_limit = r_limit;
		}
		else {
			// А можно через разрешение видимости
			Catenary::l_limit = r_limit;
			Catenary::r_limit = l_limit;
		}
	}

	Catenary& Catenary::setL(const Point& l_limit, const Point& r_limit) {
		if (l_limit.x <= r_limit.x) {
			// Можно через указатель this
			this->l_limit = l_limit;
			this->r_limit = r_limit;
		}
		else {
			// А можно через разрешение видимости
			Catenary::l_limit = r_limit;
			Catenary::r_limit = r_limit;
		}
		return *this;
	}

	// п.4: длина дуги цепной линии от ее проекции на оси абсцисс
	Type Catenary::length(const Point& p) const {
		return sqrt(pow(p.y, 2) - pow(Catenary::p.y, 2));
	}

	// п.5: радиус кривизны цепной линии от ее проекции относительно координаты по оси абсцисс
	Type Catenary::radius(const Point& p) const {
		return (pow(p.y, 2) / Catenary::p.y);
	}

	// п.6: координаты центра кривизны цепной динии в ДСК относительно координаты по оси абсцисс
	Point Catenary::center(const Point& p) const {
		Type ch = cosh(p.x / Catenary::p.y);
		Type sh = sinh(p.x / Catenary::p.y);
		Point res;
		res.x = Catenary::p.y * (ch * sh + log(ch - sh));
		res.y = 2 * Catenary::p.y * ch;
		return res;
	}

	// п.7: площадь криволинейной трапеции, образованной цепной линией и ее проекцией на ось абсцисс
	Type Catenary::area() const {
		return (Catenary::p.y * (sqrt(pow(Catenary::l_limit.y, 2) - pow(Catenary::p.y, 2)) - (sqrt(pow(Catenary::r_limit.y, 2) - pow(Catenary::p.y, 2)))));
	}

}


#include "Lab1_2.h"
#include <iomanip>


const char* msgs[] = { "0. Выйти",
"1. Ввести новые координаты вершины",
"2. Ввести новые границы цепи",
"3. Вернуть ординату цепной линии по значению абсциссы",
"4. Вернуть длину дуги цепной линии от ее проекции на оси абсцисс",
"5. Вернуть радиус кривизны цепной линии относительно координаты по оси абсцисс",
"6. Вернуть координаты центра кривизны цепной линии в декартовой системе координат относительно координаты по оси абсцисс",
"7. Вернуть площадь криволинейной трапеции, образованной цепной линией и ее проекцией на ось абсцисс (длина проекции = разности абсцисс границ)" };

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);


namespace Lab1_2 {


	// Просто за(кря)бался одно и то же писать
	void input_Type(Type& p) {
		while (Lab1_2::getNum(p))
			std::cout << "Пожалуйста, введите корректное число: --> ";
	}

	// Первая инициализация состояни класса "Цепная линия"
	Class::Catenary Input() {
		Class::Point p;
		std::cout << "Введите абсциссу вершины цепи: --> ";
		input_Type(p.x);
		while (1) {
			std::cout << "Введите ординату вершины цепи (строго положительна): --> ";
			input_Type(p.y);
			try {
				Class::Catenary line(p, 0, 0);
				Type x1, x2;
				std::cout << "Введите абсциссу первой границы цепи: --> ";
				input_Type(x1);
				std::cout << "Введите абсциссу второй границы цепи: --> ";
				input_Type(x2);
				line.setL(x1, x2);
				return line;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
		}
	}


	// Выбор номера альтернативы
	int dialog(const char* msgs[], int N) {
		const char* errmsgs = "";
		int rc, i;
		do {
			puts(errmsgs);
			errmsgs = "Ошибка! Повторите ввод!";
			for (i = 0; i < N; ++i)					// Вывод списка альтернатив
				puts(msgs[i]);
			printf("Выберите: --> ");
		} while (getNum(rc) < 0 || rc >= N);
		return rc;
	}


	// Получение информации о состоянии класса
	int D_GetStatus(const Class::Catenary& line) {
		std::cout << "-----------------------------------------------\nТекущее состояние класса: \n";
		std::cout << "Координаты вершины: " << std::fixed << std::setprecision(2) << line.getP().x << "\/" << std::fixed << std::setprecision(2) << line.getP().y << ";\n";
		std::cout << "Координаты левой граничной точки: " << std::fixed << std::setprecision(2) << line.getL_limit().x << "\/" << std::fixed << std::setprecision(2) << line.getL_limit().y << ";\n";
		std::cout << "Координаты правой граничной точки: " << std::fixed << std::setprecision(2) << line.getR_limit().x << "\/" << std::fixed << std::setprecision(2) << line.getR_limit().y << ";\n-----------------------------------------------";
		return 1;
	}

	// "1. Ввести новые координаты вершины"
	int D_SetVertex(Class::Catenary& line) {
		Class::Point p;
		std::cout << "Введите абсциссу вершины цепи: --> ";
		input_Type(p.x);
		while (1) {
			std::cout << "Введите ординату вершины цепи (строго положительна): --> ";
			input_Type(p.y);
			try {
				line.setP(p);
				std::cout << "Вершина цепи успешно изменена\n";
				return 1;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
		}
	}

	// "2. Ввести новые границы цепи"
	int D_SetBorders(Class::Catenary& line) {
		Type x1, x2;
		std::cout << "Введите абсциссу первой границы цепи: --> ";
		input_Type(x1);
		std::cout << "Введите абсциссу второй границы цепи: --> ";
		input_Type(x2);
		line.setL(x1, x2);
		return 1;
	}

	// "3. Вернуть ординату цепной линии по значению абсциссы",
	int D_GetOrdinate(Class::Catenary& line) {
		Type x, y;
		std::cout << "Введите значение абсциссы: --> ";
		input_Type(x);
		std::cout << "Координаты точки, пренадлежащей цепи с выбранной абсциссой: " << std::fixed << std::setprecision(2) << x << "\/" << std::fixed << std::setprecision(2) << line.ordinate(x) << ";\n";
		return 1;
	}

	// "4. Вернуть длину дуги цепной линии от ее проекции на оси абсцисс"
	int D_GetLength(Class::Catenary& line) {
		std::cout << "Длина дуги цепной линии от ее проекции на оси абсцисс между граничными точками: " << line.length() << "\n";
		return 1;
	}

	// "5. Вернуть радиус кривизны цепной линии относительно координаты по оси абсцисс"
	int D_GetRadius(Class::Catenary& line) {
		Type x;
		std::cout << "Введите значение абсциссы: --> ";
		input_Type(x);
		std::cout << "Радиус кривизны цепной линии относительно координаты по оси абсцисс: " << std::fixed << std::setprecision(2) << line.radius(x) << ";\n";
		return 1;
	}

	// "6. Вернуть координаты центра кривизны цепной линии в декартовой системе координат относительно координаты по оси абсцисс"
	int D_GetCenter(Class::Catenary& line) {
		Type x;
		std::cout << "Введите значение абсциссы: --> ";
		input_Type(x);
		Class::Point center = line.center(x);
		std::cout << "Координаты центра кривизны цепной линии в декартовой системе координат относительно координаты по оси абсцисс: " << std::fixed << std::setprecision(2) << center.x << "\/" << std::fixed << std::setprecision(2) << center.y << ";\n";
		return 1;
	}

	//"7. Вернуть площадь криволинейной трапеции, образованной цепной линией и ее проекцией на ось абсцисс (длина проекции = разности абсцисс границ)"
	int D_GetArea(Class::Catenary& line) {
		std::cout << "Площадь криволинейной трапеции, образованной цепной линией и ее проекцией на ось абсцисс (длина проекции = разности абсцисс границ): " << std::fixed << std::setprecision(2) << line.area() << ";\n";
		return 1;
	}

}


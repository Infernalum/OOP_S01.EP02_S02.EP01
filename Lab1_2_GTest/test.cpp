

#include "gtest\gtest.h"
#include "..\Lab1_2_GTest\CetaneryLib\CatenaryLib.h"

// Тест пустого конструктора
TEST(CetaneryConstructor, DefaultConstructor) {
	Class::Catenary def;
	ASSERT_EQ(0, def.getL_limit().x);
	ASSERT_EQ(1, def.getL_limit().y);
	ASSERT_EQ(0, def.getR_limit().x);
	ASSERT_EQ(1, def.getR_limit().y);
}

// Тест обработки исключения
TEST(CetaneryConstructor, InitTRROWConstructor) {
	Class::Point p(3, -3);
	ASSERT_ANY_THROW(Class::Catenary def(p, -2, 5));
}


// Тест инициализирующего конструктора
TEST(CetaneryConstructor, InitConstructor) {
	const Type err = 0.01;
	Class::Point p(3, 3);
	Class::Catenary def(p, -2, 5);
	ASSERT_EQ(3, def.getP().x);
	ASSERT_EQ(3, def.getP().y);
	ASSERT_EQ(-2, def.getL_limit().x);
	ASSERT_NEAR(8.22, def.getL_limit().y, err);
	ASSERT_EQ(5, def.getR_limit().x);
	ASSERT_NEAR(3.69, def.getR_limit().y, err);
}


// Тест сеттера setL
TEST(CatenaryMethods, SetL) {
	const Type err = 0.01;
	Class::Point p(3, 5);
	Type x1 = -5, x2 = 6;
	Class::Catenary def(p, -2, 5);
	ASSERT_EQ(-5, def.setL(x1, x2).getL_limit().x);
	ASSERT_NEAR(12.89, def.getL_limit().y, err);
	ASSERT_EQ(6, def.getR_limit().x);
	ASSERT_NEAR(5.93, def.getR_limit().y, err);
}

// Тест возвращения ординаты
TEST(CatenaryMethods, Ordinate) {
	const Type err = 0.01;
	Type x = 6;
	Class::Catenary def({ 3,3 }, 2, 4);
	ASSERT_NEAR(4.63, def.ordinate(x), err);
}


// Тест возвращения длины дуги
TEST(CatenaryMethods, Length) {
	const Type err = 0.01;
	Class::Catenary def({ 3,3 }, 2, 4);
	ASSERT_NEAR(6.34, def.length(), err);
}

// Тест возвращения радиуса
TEST(CatenaryMethods, Radius) {
	const Type err = 0.01;
	Type x = 2;
	Class::Catenary def({ 3,3 }, 2, 4);
	ASSERT_NEAR(3.35, def.radius(x), err);
}

// Тест возвращения координаты центра кривизны
TEST(CatenaryMethods, Center) {
	const Type err = 0.01;
	Type x = 5;
	Class::Catenary def({ 3,3 }, 2, 4);
	ASSERT_NEAR(16, def.center(x).x, err);
	ASSERT_NEAR(16.45, def.center(x).y, err);
}

// Тест возвращения площади
TEST(CatenaryMethods, Area) {
	const Type err = 0.01;
	Type x = 6;
	Class::Catenary def({ 3,3 }, 2, 4);
	ASSERT_NEAR(0, def.area(), err);
}

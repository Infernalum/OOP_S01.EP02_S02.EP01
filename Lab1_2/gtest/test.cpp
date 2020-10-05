
#include "pch.h"
#include "gtest\gtest.h"
#include "C:\Users\vladi\OneDrive\Рабочий стол\C++\Мои\Лаба 2\Lab2\Lab2\Catenary.h"

// Тест пустого конструктора
TEST(CetaneryConstructor, DefaultConstructor) {
	Class::Catenary def;
	ASSERT_EQ(0, def.getP().x);
	ASSERT_EQ(1, def.getP().y);
	ASSERT_EQ(0, def.getL_limit().x);
	ASSERT_EQ(1, def.getL_limit().y);
	ASSERT_EQ(0, def.getR_limit().x);
	ASSERT_EQ(1, def.getR_limit().y);
}

TEST(CetaneryConstructor, InitConstructor) {
	const double err = 0.01;
	Class::Point p(3,3);
	Class::Catenary def(p, -2, 5);
	ASSERT_EQ(-2, def.getL_limit().x);
	ASSERT_NEAR(-2.82, def.getL_limit().y, err);
	ASSERT_EQ(5, def.getR_limit().x);
	ASSERT_NEAR(3.69, def.getR_limit().y, err);
}
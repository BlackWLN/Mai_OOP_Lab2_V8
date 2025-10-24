#include "../include/seven.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>


TEST(FourTest, DefaultConstructor) {
  Seven s;
  std::ostringstream oss;
  oss << s;
  EXPECT_EQ(oss.str(), "0");
}

// Тест конструктора с размером и значением по умолчанию
TEST(SevenTest, SizeConstructor) {
    Seven s(3, 4);
    std::stringstream oss;
    oss << s;
    EXPECT_EQ(oss.str(), "444");
    EXPECT_THROW(Seven(3, 7), std::invalid_argument);
}

// Тест конструктора с недопустимым значением
TEST(SevenTest, InvalidDigitConstructor) {
    EXPECT_THROW(Seven(3, 7), std::invalid_argument);
    EXPECT_THROW(Seven({1, 2, 7}), std::string);
}

// Тест конструктора из строки
TEST(SevenTest, StringConstructor) {
    Seven num("1234");
    std::ostringstream oss;
    oss << num;
    EXPECT_EQ(oss.str(), "4321");
    
    // Тест с недопустимыми символами
    EXPECT_THROW(Seven("1284"), std::invalid_argument);
    EXPECT_THROW(Seven("12a4"), std::invalid_argument);
}

// Тест конструктора копирования
TEST(SevenTest, CopyConstructor) {
    Seven f1({1, 2, 3});
    Seven f2(f1);
    std::ostringstream oss;
    oss << f2;
    EXPECT_EQ(oss.str(), "321");
    EXPECT_TRUE(f1 == f2);
}   

// Тест конструктора перемещения
TEST(SevenTest, MoveConstructor) {
    Seven f1({1, 2, 3});
    Seven f2(std::move(f1));
    std::ostringstream oss;
    oss << f2;
    EXPECT_EQ(oss.str(), "321");
    std::ostringstream oss2;
    oss2 << f1;
    EXPECT_EQ(oss2.str(), "0");
}

// Тест оператора сложения
TEST(SevenTest, Plus) {
    Seven f1({1, 2, 3});
    Seven f2({4, 5, 6});
    Seven result = f1 + f2;
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "1305");
}

// Тест оператора вычитания
TEST(SevenTest, Minus) {
    Seven f1({0, 1});
    Seven f2({2});
    Seven result = f1 - f2;
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "5");
    Seven f3({1});
    Seven f4({2});
    EXPECT_THROW(f3 - f4, std::invalid_argument);
}

// Тест оператора равенства
TEST(SevenTest, Equality) {
    Seven f1({1, 2, 3});
    Seven f2({1, 2, 3});
    Seven f3({3, 2, 1});
    EXPECT_TRUE(f1 == f2);
    EXPECT_FALSE(f1 == f3);
}

// Тест оператора больше или равно
TEST(SevenTest, GreaterOrEqual) {
    Seven f1({0, 1});
    Seven f2({2});
    Seven f3({0, 1});
    Seven f4({1, 1});
    EXPECT_TRUE(f1 >= f2);
    EXPECT_TRUE(f1 >= f3);
    EXPECT_FALSE(f2 >= f4);
}

// Тест вывода в поток
TEST(SevenTest, OutputStream) {
    Seven f({3, 2, 1});
    std::ostringstream oss;
    oss << f;
    EXPECT_EQ(oss.str(), "123");
    Seven f2;
    oss.str("");
    oss << f2;
    EXPECT_EQ(oss.str(), "0");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
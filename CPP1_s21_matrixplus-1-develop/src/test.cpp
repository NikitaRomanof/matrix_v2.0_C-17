#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

TEST(TestsMatrix, constructorNonParam) {
  S21Matrix matrix;
  ASSERT_EQ(matrix.get_rows(), 2);
  ASSERT_EQ(matrix.get_cols(), 2);
}

TEST(TestsMatrix, constructorWithParam) {
  S21Matrix matrix(5, 5);
  ASSERT_EQ(matrix.get_rows(), 5);
  ASSERT_EQ(matrix.get_cols(), 5);
}

TEST(TestsMatrix, constructorCopy) {
  S21Matrix first(3, 3);
  S21Matrix second(first);
  S21Matrix rez(3, 3);
  ASSERT_TRUE(rez.eq_matrix(second));
}

TEST(TestsMatrix, constructorMove) {
  S21Matrix first(4, 4);
  S21Matrix second = std::move(first);
  S21Matrix rez(4, 4);
  ASSERT_TRUE(rez.eq_matrix(second));
}

TEST(TestsMatrix, eqMatrixTrue) {
  S21Matrix matrix(5, 5);
  S21Matrix result(5, 5);
  ASSERT_TRUE(result.eq_matrix(matrix));
}

TEST(TestsMatrix, eqMatrixFalse) {
  S21Matrix matrix(1, 1);
  S21Matrix result(1, 1);
  result(0, 0) = 1;
  ASSERT_FALSE(result.eq_matrix(matrix));
}

TEST(TestsMatrix, eqMatrixTrue2) {
  S21Matrix matrix(1, 1);
  S21Matrix result(1, 1);
  matrix(0, 0) = 1.12345678;
  result(0, 0) = 1.12345679;
  ASSERT_TRUE(result.eq_matrix(matrix));
}

TEST(TestsMatrix, eqMatrixFalse2) {
  S21Matrix matrix(1, 1);
  S21Matrix result(1, 1);
  matrix(0, 0) = 1.12345678;
  result(0, 0) = 1.12345698;
  ASSERT_FALSE(result.eq_matrix(matrix));
}

TEST(TestsMatrix, sumMatrix) {
  S21Matrix a(1, 1);
  a(0, 0) = 4.01;
  S21Matrix b(1, 1);
  b(0, 0) = 5.01;
  a.sum_matrix(b);
  S21Matrix c(1, 1);
  c(0, 0) = 9.02;
  ASSERT_TRUE(c.eq_matrix(a));
}

TEST(TestsMatrix, operatorPlus) {
  S21Matrix a(1, 1);
  a(0, 0) = 1.01;
  S21Matrix b(1, 1);
  b(0, 0) = 4.01;
  a = a + b;
  S21Matrix c(1, 1);
  c(0, 0) = 5.02;
  ASSERT_TRUE(c.eq_matrix(a));
}

TEST(TestsMatrix, operatorPlusAssign) {
  S21Matrix a(1, 1);
  a(0, 0) = 10.01;
  S21Matrix b(1, 1);
  b(0, 0) = 1.01;
  a += b;
  S21Matrix c(1, 1);
  c(0, 0) = 11.02;
  ASSERT_TRUE(c.eq_matrix(a));
}

TEST(TestsMatrix, subMatrix) {
  S21Matrix a(1, 1);
  a(0, 0) = 4.02;
  S21Matrix b(1, 1);
  b(0, 0) = 3.01;
  a.sub_matrix(b);
  S21Matrix c(1, 1);
  c(0, 0) = 1.01;
  ASSERT_TRUE(c.eq_matrix(a));
}

TEST(TestsMatrix, operatorMinus) {
  S21Matrix a(1, 1);
  a(0, 0) = 3.02;
  S21Matrix b(1, 1);
  b(0, 0) = 1.01;
  a = a - b;
  S21Matrix c(1, 1);
  c(0, 0) = 2.01;
  ASSERT_TRUE(c.eq_matrix(a));
}

TEST(TestsMatrix, operatorMinusAssign) {
  S21Matrix a(1, 1);
  a(0, 0) = 5.03;
  S21Matrix b(1, 1);
  b(0, 0) = 4.02;
  a -= b;
  S21Matrix c(1, 1);
  c(0, 0) = 1.01;
  ASSERT_TRUE(c.eq_matrix(a));
}

TEST(TestsMatrix, mulMatrix) {
  S21Matrix a(2, 2);
  a(0, 0) = 2;
  S21Matrix b(2, 2);
  b(0, 0) = 2;
  a.mul_matrix(b);
  S21Matrix c(2, 2);
  c(0, 0) = 4;
  ASSERT_TRUE(c.eq_matrix(a));
}

TEST(TestsMatrix, operatorMul) {
  S21Matrix a(2, 2);
  a(0, 0) = 2;
  S21Matrix b(2, 2);
  b(0, 0) = 2;
  a = a * b;
  S21Matrix c(2, 2);
  c(0, 0) = 4;
  ASSERT_TRUE(c.eq_matrix(a));
}

TEST(TestsMatrix, operatorMulAssign) {
  S21Matrix a(2, 2);
  a(0, 0) = 2;
  S21Matrix b(2, 2);
  b(0, 0) = 2;
  a *= b;
  S21Matrix c(2, 2);
  c(0, 0) = 4;
  ASSERT_TRUE(c.eq_matrix(a));
}

TEST(TestsMatrix, mulNumber) {
  S21Matrix a(2, 2);
  a(0, 0) = 2;
  a.mul_number(5);
  S21Matrix b(2, 2);
  b(0, 0) = 10;
  ASSERT_TRUE(b.eq_matrix(a));
}

TEST(TestsMatrix, operatorMulNumber) {
  S21Matrix a(2, 2);
  a(0, 0) = 2;
  a = a * 2;
  S21Matrix b(2, 2);
  b(0, 0) = 4;
  ASSERT_TRUE(b.eq_matrix(a));
}

TEST(TestsMatrix, operatorMulAssignNumber) {
  S21Matrix a(2, 2);
  a(0, 0) = 2;
  a *= 2;
  S21Matrix b(2, 2);
  b(0, 0) = 4;
  ASSERT_TRUE(b.eq_matrix(a));
}

TEST(TestsMatrix, getRows) {
  S21Matrix a(3, 3);
  ASSERT_EQ(a.get_rows(), 3);
}

TEST(TestsMatrix, getCols) {
  S21Matrix a(3, 3);
  ASSERT_EQ(a.get_cols(), 3);
}

TEST(TestsMatrix, setRows) {
  S21Matrix a(3, 3);
  a.set_rows(4);
  ASSERT_EQ(a.get_rows(), 4);
}

TEST(TestsMatrix, setCols) {
  S21Matrix a(3, 3);
  a.set_cols(2);
  ASSERT_EQ(a.get_cols(), 2);
}

TEST(TestsMatrix, transpose) {
  S21Matrix a(3, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  a(2, 0) = 5;
  a(2, 1) = 6;
  S21Matrix b(2, 3);
  b(0, 0) = 1;
  b(0, 1) = 3;
  b(0, 2) = 5;
  b(1, 0) = 2;
  b(1, 1) = 4;
  b(1, 2) = 6;
  a = a.transpose();
  ASSERT_TRUE(a.eq_matrix(b));
}
TEST(TestsMatrix, determinant) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;
  ASSERT_EQ(0, a.determinant());
}

TEST(TestsMatrix, compliment) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 0;
  a(1, 1) = 4;
  a(1, 2) = 2;
  a(2, 0) = 5;
  a(2, 1) = 2;
  a(2, 2) = 1;
  S21Matrix b(3, 3);
  b(0, 0) = 0;
  b(0, 1) = 10;
  b(0, 2) = -20;
  b(1, 0) = 4;
  b(1, 1) = -14;
  b(1, 2) = 8;
  b(2, 0) = -8;
  b(2, 1) = -2;
  b(2, 2) = 4;
  a = a.calc_complements();
  ASSERT_TRUE(a.eq_matrix(b));
}

TEST(TestsMatrix, inverse) {
  S21Matrix a(3, 3);
  a(0, 0) = 2;
  a(0, 1) = 5;
  a(0, 2) = 7;
  a(1, 0) = 6;
  a(1, 1) = 3;
  a(1, 2) = 4;
  a(2, 0) = 5;
  a(2, 1) = -2;
  a(2, 2) = -3;
  S21Matrix b(3, 3);
  b(0, 0) = 1;
  b(0, 1) = -1;
  b(0, 2) = 1;
  b(1, 0) = -38;
  b(1, 1) = 41;
  b(1, 2) = -34;
  b(2, 0) = 27;
  b(2, 1) = -29;
  b(2, 2) = 24;
  a = a.inverse_matrix();
  ASSERT_TRUE(a.eq_matrix(b));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

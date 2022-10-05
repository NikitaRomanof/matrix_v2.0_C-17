#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <exception>
#include <iostream>

class MatrixException : public std::exception {
 private:
  std::string str;

 public:
  explicit MatrixException(std::string strExcep) : str(strExcep) {}
  ~MatrixException() throw() {}
  const char* what() const throw() { return str.c_str(); }
};

class S21Matrix {
 private:
  void memoryAllocation();
  void memoryClean();
  void sumOrSub(const S21Matrix& other, int sign);
  int _rows = 0, _cols = 0;
  double** _matrix = nullptr;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();
  bool eq_matrix(const S21Matrix& other);
  void sum_matrix(const S21Matrix& other);
  void sub_matrix(const S21Matrix& other);
  void mul_number(const double num);
  void mul_matrix(const S21Matrix& other);
  S21Matrix transpose();
  S21Matrix calc_complements();
  double determinant();
  S21Matrix inverse_matrix();
  S21Matrix getReducedMatrix(int delRow, int delColumn);

  S21Matrix operator=(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double number);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const double number);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  double& operator()(int row, int col);

  int get_rows();
  void set_rows(int rows);
  int get_cols();
  void set_cols(int cols);
};

#endif  // SRC_S21_MATRIX_OOP_H_"

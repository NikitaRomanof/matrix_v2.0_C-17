#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  _rows = 2;
  _cols = 2;
  memoryAllocation();
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    MatrixException nonExist(
        "The number of rows/columns of the matrix is less than 1");
    throw nonExist;
  }
  _rows = rows;
  _cols = cols;
  memoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  _rows = other._rows;
  _cols = other._cols;
  memoryAllocation();
  for (int i = 0; i < _rows; i++) {
    memcpy(_matrix[i], other._matrix[i], _cols * sizeof(double));
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  if (this == &other) {
    MatrixException nonExist(
        "The object passes itself to the move constructor");
    throw nonExist;
  }
  std::swap(_rows, other._rows);
  std::swap(_cols, other._cols);
  std::swap(_matrix, other._matrix);
}

S21Matrix::~S21Matrix() { memoryClean(); }

void S21Matrix::memoryAllocation() {
  _matrix = new double*[_rows];
  _matrix[0] = new double[_rows * _cols]();
  for (int i = 1; i < _rows; i++) {
    _matrix[i] = _matrix[0] + i * _cols;
  }
}

void S21Matrix::memoryClean() {
  if (_matrix != nullptr) {
    delete[] _matrix[0];
    delete[] _matrix;
  }
}

void S21Matrix::sumOrSub(const S21Matrix& other, int sign) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] = _matrix[i][j] + (sign * other._matrix[i][j]);
    }
  }
}

bool S21Matrix::eq_matrix(const S21Matrix& other) {
  bool rez = false;
  if (_rows == other._rows && _cols == other._cols) {
    rez = true;
    for (int i = 0; i < _rows && rez == true; i++) {
      for (int j = 0; j < _cols && rez == true; j++) {
        if (fabs(_matrix[i][j] - other._matrix[i][j]) >= 1e-7) {
          rez = false;
        }
      }
    }
  }
  return rez;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
  if (_rows != other._rows || _cols != other._cols) {
    MatrixException inconsistency("Rows/columns of matrices are not equal");
    throw inconsistency;
  }
  sumOrSub(other, 1);
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
  if (_rows != other._rows || _cols != other._cols) {
    MatrixException inconsistency("Rows/columns of matrices are not equal");
    throw inconsistency;
  }
  sumOrSub(other, -1);
}

void S21Matrix::mul_number(const double num) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] = _matrix[i][j] * num;
    }
  }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
  if (_cols != other._rows) {
    MatrixException nonExist("Columns are not equal to rows");
    throw nonExist;
  }
  S21Matrix buf(_rows, other._cols);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < other._cols; j++) {
      for (int n = 0; n < other._rows; n++) {
        buf._matrix[i][j] += _matrix[i][n] * other._matrix[n][j];
      }
    }
  }
  *this = buf;
}

S21Matrix S21Matrix::transpose() {
  S21Matrix buf(_cols, _rows);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      buf._matrix[j][i] = _matrix[i][j];
    }
  }
  return buf;
}

S21Matrix S21Matrix::getReducedMatrix(int rowsReduced, int colsReduced) {
  S21Matrix buf(_rows - 1, _cols - 1);
  int newRows = 0, newCols = 0;
  for (int i = 0; i < _rows; i++) {
    if (i != rowsReduced) {
      for (int j = 0; j < _rows; j++) {
        if (j != colsReduced) {
          buf._matrix[newRows][newCols] = _matrix[i][j];
          newCols++;
        }
      }
      newRows++;
      newCols = 0;
    }
  }
  return buf;
}

double S21Matrix::determinant() {
  double det = 0.0;
  if (_rows != _cols) {
    MatrixException nonExist("Error, matrix is not square");
    throw nonExist;
  }
  if (_rows == 1) {
    det = _matrix[0][0];
  } else if (_rows == 2) {
    det = _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
  } else {
    for (int i = 0; i < _rows; i++) {
      S21Matrix buf = getReducedMatrix(i, 0);
      det += _matrix[i][0] * pow(-1, i) * buf.determinant();
    }
  }
  return det;
}

S21Matrix S21Matrix::calc_complements() {
  if (_rows != _cols || _rows == 1) {
    MatrixException nonExist("Error, matrix is not square");
    throw nonExist;
  }
  S21Matrix rez(_rows, _cols);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      S21Matrix buf = getReducedMatrix(i, j);
      rez._matrix[i][j] = pow(-1, i + j) * buf.determinant();
    }
  }
  return rez;
}

S21Matrix S21Matrix::inverse_matrix() {
  double det = determinant();
  if (_rows != _cols || det == 0.0 || _rows == 1) {
    MatrixException nonExist("Determinant is zero, or matrix is not square");
    throw nonExist;
  }
  S21Matrix rez(_rows, _cols);
  rez = calc_complements();
  rez = rez.transpose();
  rez.mul_number(1.0 / det);
  return rez;
}

S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) {
    MatrixException nonExist("Cannot assign an object's value to itself");
    throw nonExist;
  }
  memoryClean();
  _rows = other._rows;
  _cols = other._cols;
  memoryAllocation();
  for (int i = 0; i < _rows; i++) {
    memcpy(_matrix[i], other._matrix[i], _cols * sizeof(double));
  }
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  sum_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  sub_matrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double other) {
  mul_number(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  mul_matrix(other);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) { return eq_matrix(other); }

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix buf(*this);
  buf.sum_matrix(other);
  return buf;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix buf(*this);
  buf.sub_matrix(other);
  return buf;
}

S21Matrix S21Matrix::operator*(const double other) {
  S21Matrix buf(*this);
  buf.mul_number(other);
  return buf;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix buf(*this);
  buf.mul_matrix(other);
  return buf;
}

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= _rows || col >= _cols) {
    MatrixException non("Incorrect row/col");
    throw non;
  }
  return _matrix[row][col];
}
int S21Matrix::get_rows() { return _rows; }

int S21Matrix::get_cols() { return _cols; }

void S21Matrix::set_rows(int rows) {
  S21Matrix buf(rows, _cols);
  int minRow = _rows > rows ? rows : _rows;
  for (int i = 0; i < minRow; i++) {
    for (int j = 0; j < _cols; j++) {
      buf._matrix[i][j] = _matrix[i][j];
    }
  }
  *this = buf;
}

void S21Matrix::set_cols(int cols) {
  S21Matrix buf(_rows, cols);
  int minCol = _cols > cols ? cols : _cols;
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < minCol; j++) {
      buf._matrix[i][j] = _matrix[i][j];
    }
  }
  *this = buf;
}

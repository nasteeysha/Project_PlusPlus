#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(1), cols_(1) {
  S21Matrix temp(1, 1);
  matrix_ = temp.matrix_;
  temp.matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (cols < 1 || rows < 1) throw std::logic_error("Incorrect size");

  matrix_ = new double*[rows_]();
  matrix_[0] = new double[rows_ * cols_]();
  for (int i = 1; i != rows_; ++i) matrix_[i] = matrix_[i - 1] + cols_;
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  S21Matrix temp(other.rows_, other.cols_);

  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      temp.matrix_[i][j] = other.matrix_[i][j];
    }
  }

  matrix_ = temp.matrix_;
  temp.matrix_ = nullptr;
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() noexcept {
  if (matrix_ != nullptr) {
    delete[] matrix_[0];
    delete[] matrix_;
    rows_ = 0;
    cols_ = 0;
  }
}

void S21Matrix::SetRows(int row) {
  if (row < 1) throw std::logic_error("invalid new matrix size");

  S21Matrix result(row, cols_);

  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i < rows_) result.matrix_[i][j] = matrix_[i][j];
    }
  }

  std::swap(result.matrix_, matrix_);

  rows_ = result.rows_;
  cols_ = result.cols_;

  result.rows_ = 0;
  result.cols_ = 0;
}

void S21Matrix::SetCols(int col) {
  if (col < 1) throw std::logic_error("invalid new matrix size");

  S21Matrix result(rows_, col);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < col; ++j) {
      if (j < cols_) result.matrix_[i][j] = matrix_[i][j];
    }
  }

  std::swap(result.matrix_, matrix_);

  rows_ = result.rows_;
  cols_ = result.cols_;

  result.rows_ = 0;
  result.cols_ = 0;
}

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) return false;
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error(
        "Different number of rows or columns in these matrices");

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error(
        "Different number of rows or columns in these matrices");

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::logic_error(
        "Different number of a.columns and b.rows in this matrices");

  S21Matrix tmp(rows_, other.cols_);

  for (int i = 0; i < tmp.rows_; ++i) {
    for (int j = 0; j < tmp.cols_; ++j) {
      for (int k = 0; k < other.rows_; k++) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  std::swap(tmp.matrix_, matrix_);

  rows_ = tmp.rows_;
  cols_ = tmp.cols_;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix tmp(cols_, rows_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      tmp.matrix_[j][i] = matrix_[i][j];
    }
  }

  return tmp;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_)
    throw std::logic_error(
        "Different number of rows or columns in this matrix");

  int sub_j, sub_i;
  double det, complement;

  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix tmp(rows_ - 1, cols_ - 1);

      sub_i = 0;
      for (int k = 0; k < rows_; k++) {
        if (k == i) continue;
        sub_j = 0;

        for (int l = 0; l < cols_; l++) {
          if (l == j) continue;
          tmp.matrix_[sub_i][sub_j] = matrix_[k][l];
          ++sub_j;
        }
        ++sub_i;
      }

      det = tmp.Determinant();
      complement = det * pow(-1, i + j + 2);
      result.matrix_[i][j] = complement;
    }
  }

  return result;
}

double S21Matrix::Determinant() const {
  int i, j, k, sign;
  double det = 0.0, result;

  if (rows_ != cols_)
    throw std::logic_error("Different rows or columns in this matrices");

  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix tmp(rows_ - 1, cols_ - 1);

    for (k = 0; k < cols_; ++k) {
      for (i = 1; i < rows_; ++i) {
        for (j = 0; j < cols_; ++j) {
          if (j != k) {
            tmp.matrix_[i - 1][j < k ? j : j - 1] = matrix_[i][j];
          }
        }
      }

      if (k % 2 == 0) {
        sign = 1;
      } else {
        sign = -1;
      }

      result = tmp.Determinant();
      det += sign * matrix_[0][k] * (result);
    }

    result = det;
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (det == 0.0)
    throw std::logic_error(
        "The inverse matrix cannot be found because the determinant of the "
        "matrix is zero.");

  S21Matrix subres = CalcComplements();
  S21Matrix result = subres.Transpose();

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] /= det;
    }
  }

  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);

  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);

  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);

  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) const noexcept {
  S21Matrix result(*this);

  result.MulNumber(num);
  return result;
}

S21Matrix& S21Matrix::operator=(
    const S21Matrix& other) {  //оператор присваивания копированием
  if (other.matrix_ == this->matrix_) return *this;

  S21Matrix result(other.rows_, other.cols_);

  result.rows_ = other.rows_;
  result.cols_ = other.cols_;

  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      result.matrix_[i][j] = other.matrix_[i][j];
    }
  }

  std::swap(result.matrix_, matrix_);

  rows_ = result.rows_;
  cols_ = result.cols_;

  result.rows_ = 0;
  result.cols_ = 0;

  return *this;
}
S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }

  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) noexcept {
  MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
    throw std::logic_error("Error with rows and columns");

  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
    throw std::logic_error("Error with rows and columns");

  return matrix_[row][col];
}
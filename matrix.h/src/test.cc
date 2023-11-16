#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(Constructor, basic) {
  S21Matrix matrix;

  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_EQ(matrix.GetRows(), 1);
}

TEST(Constructor, rows_cols) {
  S21Matrix matrix(5, 5);

  EXPECT_EQ(matrix.GetRows(), 5);
  EXPECT_EQ(matrix.GetCols(), 5);
}

TEST(Constructor, copy) {
  S21Matrix matrix_source(2, 2);
  S21Matrix matrix_dest(matrix_source);

  EXPECT_TRUE(matrix_source == matrix_dest);
}

TEST(Constructor, move) {
  S21Matrix matrix_source(2, 2);
  S21Matrix matrix_dest(std::move(matrix_source));

  EXPECT_FALSE(matrix_source == matrix_dest);
}

TEST(EqMatrix, true) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(EqMatrix, false) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 2);

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(SumMatrix, normal) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1.SumMatrix(matrix2));
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 12.0);
}

TEST(SubMatrix, normal) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1.SubMatrix(matrix2));
  EXPECT_DOUBLE_EQ(matrix1(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), -4.0);
}

TEST(MulNumber, normal) {
  S21Matrix matrix1(2, 2);
  double num = 5.0;

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix1.MulNumber(num);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 15.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 20.0);
}

TEST(MulMatrix, normal) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1.MulMatrix(matrix2));
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 19.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 22.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 43.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 50.0);
}

TEST(Transpose, normal) {
  S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(matrix1.Transpose()(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix1.Transpose()(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(matrix1.Transpose()(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix1.Transpose()(1, 1), 4.0);
}

TEST(CalcComplements, normal) {
  S21Matrix matrix1(3, 3);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;
  matrix1(2, 0) = 7.0;
  matrix1(2, 1) = 8.0;
  matrix1(2, 2) = 9.0;

  EXPECT_NO_THROW(matrix1.CalcComplements());
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(0, 0), -3.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(0, 2), -3.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(1, 1), -12.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(1, 2), 6.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(2, 0), -3.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(2, 1), 6.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(2, 2), -3.0);
}

TEST(Determinant, normal) {
  S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  EXPECT_NO_THROW(matrix1.Determinant());
  EXPECT_DOUBLE_EQ(matrix1.Determinant(), -2.0);
}

TEST(InverseMatrix, normal) {
  S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  EXPECT_NO_THROW(matrix1.InverseMatrix());
  EXPECT_DOUBLE_EQ(matrix1.InverseMatrix()(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(matrix1.InverseMatrix()(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(matrix1.InverseMatrix()(1, 0), 1.5);
  EXPECT_DOUBLE_EQ(matrix1.InverseMatrix()(1, 1), -0.5);
}

TEST(GetRows, normal) {
  S21Matrix matrix1(3, 2);

  EXPECT_EQ(matrix1.GetRows(), 3);
}

TEST(SetRows, less) {
  S21Matrix matrix1(3, 3);

  EXPECT_NO_THROW(matrix1.SetRows(2));
  EXPECT_EQ(matrix1.GetRows(), 2);
}

TEST(SetRows, more) {
  S21Matrix matrix1(2, 2);

  EXPECT_NO_THROW(matrix1.SetRows(3));
  EXPECT_EQ(matrix1.GetRows(), 3);
  EXPECT_DOUBLE_EQ(matrix1(2, 0), 0);
  EXPECT_DOUBLE_EQ(matrix1(2, 1), 0);
}

TEST(GetCols, normal) {
  S21Matrix matrix1(2, 3);

  EXPECT_EQ(matrix1.GetCols(), 3);
}

TEST(SetCols, less) {
  S21Matrix matrix1(3, 3);

  EXPECT_NO_THROW(matrix1.SetCols(2));
  EXPECT_EQ(matrix1.GetCols(), 2);
}

TEST(SetCols, more) {
  S21Matrix matrix1(2, 2);

  EXPECT_NO_THROW(matrix1.SetCols(3));
  EXPECT_EQ(matrix1.GetCols(), 3);
  EXPECT_DOUBLE_EQ(matrix1(0, 2), 0);
  EXPECT_DOUBLE_EQ(matrix1(1, 2), 0);
}

TEST(Plus, normal) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 + matrix2);
  S21Matrix result = matrix1 + matrix2;
  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST(AssnPlus, normal) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 += matrix2);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 12.0);
}

TEST(Minus, normal) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 - matrix2);
  S21Matrix result = matrix1 - matrix2;
  EXPECT_DOUBLE_EQ(result(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -4.0);
}

TEST(AssnMinus, normal) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 -= matrix2);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), -4.0);
}

TEST(MulMatrixOperator, normal) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 * matrix2);
  S21Matrix result = matrix1 * matrix2;
  EXPECT_DOUBLE_EQ(result(0, 0), 19.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 22.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 43.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 50.0);
}

TEST(MulNumberOperator, normal) {
  S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix result = matrix1 * 5.0;
  EXPECT_DOUBLE_EQ(result(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 15.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 20.0);
}

TEST(AssnMulMatrixOperator, normal) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 *= matrix2);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 19.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 22.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 43.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 50.0);
}

TEST(AssnMulNumberOperator, normal) {
  S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix1 *= 5.0;
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 15.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 20.0);
}

TEST(Assn, normal) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  matrix1 = matrix2;
  EXPECT_EQ(matrix1.GetRows(), 3);
  EXPECT_EQ(matrix1.GetCols(), 3);
}

TEST(EqMatrixOperator, true) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(EqMatrixOperator, false) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 2);

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(Staples, normal) {
  S21Matrix matrix1(2, 2);

  EXPECT_EQ(matrix1(1, 1), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

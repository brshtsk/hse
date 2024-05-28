#include "matrix.h"

#include <algorithm>
#include <stdexcept>

Matrix::Matrix(size_t rowsNum, size_t colsNum)
    : Matrix() {
  // Либо два нуля (пустая м-ца), либо нет нулей.
  if (!rowsNum && !colsNum) {
    return;
  }

  // Для использования стандартных исключений требуется включение большого заголовка,
  // который не стоит тащить в .h файле.

  if (!rowsNum || !colsNum) {
    throw std::invalid_argument("Both dimensions must be zero or non-zero.");
  }

  rowsNum_ = rowsNum;
  colsNum_ = colsNum;
  storage_ = new double[rowsNum * colsNum];

}

Matrix::Matrix(size_t rowsNum, size_t colsNum, double def)
    : Matrix(rowsNum, colsNum) {
  for (size_t i = 0; i < rowsNum; ++i) {
    for (size_t j = 0; j < colsNum; ++j) {
      GetEl(i, j) = def;
    }
  }
}

void Matrix::CheckIJ(size_t i, size_t j) const {
  if (i >= rowsNum_ || j >= colsNum_) {
    throw std::out_of_range("Such matrix element doesn't exist.");
  }
}

Matrix::Matrix(const Matrix &other)
    : rowsNum_{other.rowsNum_},
      colsNum_{other.colsNum_},
      storage_{other.storage_ ? new double[other.rowsNum_ * other.colsNum_] : nullptr} {
  for (size_t i = 0; i < other.rowsNum_; ++i) {
    for (size_t j = 0; j < other.colsNum_; ++j) {
      GetEl(i, j) = other.GetEl(i, j);
    }
  }
}

Matrix &Matrix::operator=(const Matrix &rhs) {
  // Мы не будем это использовать, но вообще.
  // Matrix &lhs = *this;

  if (&rhs == this) {
    return *this;
  }
  // Вариант 1: "в лоб". Освобождаем использованный массив из кучи.
/*    delete[] storage_;

    rowsNum_ = rhs.rowsNum_;
    colsNum_ = rhs.colsNum_;
    storage_ = rhs.storage_ ? new double[rowsNum_ * colsNum_] : nullptr; // В этом месте может вылезти исключение,
                                                                         // если нет места под новый массив double.

    for (size_t i = 0; i < rhs.rowsNum_; ++i) {
      for (size_t j = 0; j < rhs.colsNum_; ++j) {
        GetEl(i, j) = rhs.GetEl(i, j);
      }
    }
 */

  // Вариант 2. Использование идиомы "Copy and Swap".
  // 1. Мы хотим все свести к конструктору копирования.
  // 2. Реализуем специальную функцию Swap, которая будет КОВАРНО обменивать ресурсами, которыми владеют объекты.

  // Нужно для реализации x=y=k, чтобы приходило к виду x=k.

  Matrix temp = rhs;
  Swap(*this, temp);
  return *this;
}

void Matrix::Swap(Matrix &lhs, Matrix &rhs) {
  // Swap никогда не кидает исключения по E16.
  std::swap(lhs.rowsNum_, rhs.rowsNum_);
  std::swap(lhs.colsNum_, rhs.colsNum_);
  std::swap(lhs.storage_, rhs.storage_);
}

Matrix &Matrix::operator=(Matrix &&victim) {
  // Компилятор сам применяет MAO.
  delete storage_;
  rowsNum_ = victim.rowsNum_;
  victim.rowsNum_ = 0;
  colsNum_ = victim.colsNum_;
  victim.colsNum_ = 0;
  storage_ = victim.storage_;
  victim.storage_ = nullptr;
  return *this;
}
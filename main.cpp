// ToDo: спросить про категории итераторов.

/*
 * Разработать такой класс Матрица:
 *
 * 1) Для представления элементов используем наиболее компактное
 * 2) Используем правильное управление ресурсами (памятью):
 * - Распределение
 * - Освобождение
 * - Глубокое копирование
 * 3) Добавляем операционную симантику для объекта Матрица (+, *, транспониирование, ==, !=)
 * - Сделаем перегрузку операторов
 * 4) Для представления составных элементов Матрицы (столбцы, строки) создадим легковесные обертки,
 * которые можнь передавать по значению (аналогия с итераторами и string_view), не забываем про константность
 * 5) Добавляем в Матрицу умение быть хорошо воспитанным контейнером:
 * - Итераторы, begin'ы, end'ы
 * 6) Научим Матрицу быть перемещаемым объектом (НЛО)
 * 7) Сделаем Матрицу шаблоном, чтобы это была матрица произвольных значений (Матрица T)
 */

#include <iostream>
#include <cassert>

#include "matrix.h"

void test01() {
  assert(true);
}

void test02() {
  Matrix m;
  assert(true);
}

void test03() {
  Matrix m(3, 4, 42);
  assert(m.GetRowsNum() == 3 && m.GetColsNum() == 4);
  assert(m.GetEl(1, 2) == 42);
}

void PrintMatrixRow(Matrix::ConstRow row) {
  for (size_t i = 0; i < row.size(); ++i) {
    std::cout << row[i] << ' ';
  }
  std::cout << '\n';
}

void PrintMatrixCol(Matrix::ConstColumn col) {
  for (size_t i = 0; i < col.size(); ++i) {
    std::cout << col[i] << ' ';
  }
  std::cout << '\n';
}

// row похож на итератор, так что передаем его по значению.
void DoubleRow(Matrix::ConstRow row) {
  for (size_t i = 0; i < row.size(); ++i) {
    row[i] *= 2;
  }
}

void TripleCol(Matrix::ConstColumn col) {
  for (size_t i = 0; i < col.size(); ++i) {
    col[i] *= 3;
  }
}

void test04() {
  std::cout << "test04" << std::endl;
  Matrix m(3, 4, 42);

  // Matrix::Row row(1, &m); // Ужас
  PrintMatrixRow(m[1]);
  DoubleRow(m[1]);
  PrintMatrixRow(m[1]);
  // PrintMatrixCol(m(2));
}

void PrintKthRow(const Matrix &m, size_t k) {
  PrintMatrixRow(m[k]);
}

void PrintKthCol(const Matrix &m, size_t k) {
  PrintMatrixCol(m(k));
}

void test05() {
  Matrix m(3, 4, 42);
  PrintKthRow(m, 1);
}

void test06() {
  // Приверяем функции для ConstColumn, приведение Column в ConstColumn.
  std::cout << "test07" << std::endl;
  Matrix m{5, 2, 14};
  TripleCol(m(1));
  PrintKthCol(m, 1);
  PrintKthRow(m, 0);
}

void test07() {
  // Смотрим изменения матрицы через Row, Column.
  Matrix m{6, 7, 55};
  m[3][5] = 9;
  m(0)[4] = 11;
  for (size_t i = 0; i < m.GetRowsNum(); ++i) {
    for (size_t j = 0; j < m.GetColsNum(); ++j) {
      assert(m[i][j] == m(j)[i]);
    }
  }
}

void test08() {
  // Проверяем оператор копирования.
  Matrix m1{3, 4, 42};
  Matrix m2 = m1;
  assert(m1.GetRowsNum() == m2.GetRowsNum() && m1.GetColsNum() == m2.GetColsNum());
  for (size_t i = 0; i < m1.GetRowsNum(); ++i) {
    for (size_t j = 0; j < m1.GetColsNum(); ++j) {
      assert(m1[i][j] == m2[i][j]);
    }
  }
}

void test09() {
  // Проверяем оператор присваивания.
  Matrix m1{3, 4, 42};
  Matrix m2;
  m2 = m1;
  assert(m1.GetRowsNum() == m2.GetRowsNum() && m1.GetColsNum() == m2.GetColsNum());
  for (size_t i = 0; i < m1.GetRowsNum(); ++i) {
    for (size_t j = 0; j < m1.GetColsNum(); ++j) {
      assert(m1[i][j] == m2[i][j]);
    }
  }
}

void CheckEquality(const Matrix copy, const Matrix &orig) {
  for (size_t i = 0; i < copy.GetRowsNum(); ++i) {
    for (size_t j = 0; j < copy.GetColsNum(); ++j) {
      assert(copy[i][j] == orig[i][j]);
    }
  }
  orig[2][2] = -copy[2][2];
  assert(orig[2][2] != copy[2][2]);
}

void test10() {
  // Проверяем корректность передачи матрицы как аргумент функции (вызывается ОП).
  Matrix m{4, 4, 14};
  CheckEquality(m, m);
}

class Foo {
 private:
  static size_t count_;
  size_t ind_;

  void Print(const char *note) {
    std::cout << "count: " << count_ << ", " << note << ", instance num = " << ind_ << std::endl;
  }
 public:
  Foo() {
    ind_ = ++count_;
    Print("Default constructor");
  }

  Foo(Foo &old) {
    ind_ = ++count_;
    Print("Copy constructor");
  }

  size_t GetCount() const {
    return count_;
  }

  Foo(Foo &&old) {
    ind_ = ++count_;
    Print("Move constructor");
  }
};

// Статические поля нужно конструировать вне класса.
size_t Foo::count_ = 0;

Foo test11_1() {
  Foo f;
  return f;
}

void test11() {
  Foo foo;
  Foo bar = test11_1();
}

void test12() {
  Matrix m(26, 2, 42);
  for (Matrix::value_type it : m) {
    std::cout << it << ' ';
  }
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
  test08();
  test09();
  test10();
  test11();
  test12();
  std::cout << "Allright";
  return 0;
}
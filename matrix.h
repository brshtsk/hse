#ifndef MYMATRIX_MATRIX_H
#define MYMATRIX_MATRIX_H

#include <cstddef>

class Matrix {
 public:
  // Представляет строку.
  class Row {
    friend class Matrix;
   public:
    size_t size() const {
      return matrix_->GetColsNum();
    }

    double operator[](size_t colNum) const {
      return matrix_->GetEl(rowNum_, colNum);
    }

    double &operator[](size_t colNum) {
      return matrix_->GetEl(rowNum_, colNum);
    }

   private:
    Row(size_t rowNum, Matrix *matrix)
        : rowNum_(rowNum), matrix_(matrix) {}
   private:
    size_t rowNum_;
    Matrix *matrix_;
  };

  // Представляет строку, которую нельзя менять.
  class ConstRow {
    friend class Matrix;
   public:
    size_t size() const {
      return const_matrix_->GetColsNum();
    }

    double operator[](size_t colNum) const {
      return const_matrix_->GetEl(rowNum_, colNum);
    }

    double &operator[](size_t colNum) {
      return const_matrix_->GetEl(rowNum_, colNum);
    }

   public:
    // Конструктор перевода Row в ConstRow.
    ConstRow(const Row &other) : rowNum_(other.rowNum_), const_matrix_{other.matrix_} {}

   private:
    ConstRow(size_t rowNum, const Matrix *matrix)
        : rowNum_(rowNum), const_matrix_(matrix) {}
   private:
    size_t rowNum_;
    const Matrix *const_matrix_;
  };

  class Column {
    friend class Matrix;
   public:
    size_t size() const {
      return matrix_->GetRowsNum();
    }

    double operator[](size_t rowNum) const {
      return matrix_->GetEl(rowNum, colNum_);
    }

    double &operator[](size_t rowNum) {
      return matrix_->GetEl(rowNum, colNum_);
    }

   private:
    Column(size_t colNum, Matrix *matrix)
    : colNum_(colNum), matrix_(matrix) {}
   private:
    size_t colNum_;
    Matrix *matrix_;
  };

  class ConstColumn {
    friend class Matrix;
   public:
    size_t size() const {
      return const_matrix_->GetRowsNum();
    }

    double operator[](size_t rowNum) const {
      return const_matrix_->GetEl(rowNum, colNum_);
    }

    double &operator[](size_t rowNum) {
      return const_matrix_->GetEl(rowNum, colNum_);
    }

   public:
    ConstColumn(const Column &other) : colNum_(other.colNum_), const_matrix_{other.matrix_} {}

   private:
    ConstColumn(size_t colNum, const Matrix *matrix)
        : colNum_(colNum), const_matrix_(matrix) {}
   private:
    size_t colNum_;
    const Matrix *const_matrix_;
  };

 public:
  Matrix()
      : storage_{} // Выполняется инициализация объектов,
      , rowsNum_{} // то есть вызов конструкторов соответсвующих типов.
      , colsNum_{} // Круглые скобочки тоже можно, например _rows_am(0).
  {
    // В следующих 3 строках перезаписываем ранее инициализированные объекты,
    // поэтому использовать это мето для реализации слишком поздно.
    // Происходит операция присваивания, которая происходит долго.
    // _storage = nullptr;
    // _rows_am = 0;
    // _cols_am = 0;
  }

  Matrix(size_t rowsNum, size_t colsNum);
  Matrix(size_t rowsNum, size_t colsNum, double def);

  ~Matrix() {
    delete storage_; // Делать delete для nullptr безопасно.
  }

 public:
  // Конструктор копирования.
  Matrix(const Matrix &other);

 public:
  double At(size_t i, size_t j) const {
    CheckIJ(i, j);
    return storage_[CalcOffset(i, j)];
  }

  double &At(size_t i, size_t j) {
    CheckIJ(i, j);
    return GetEl(i, j);
  }

  double &GetEl(size_t i, size_t j) {
    return storage_[CalcOffset(i, j)];
  }

  size_t CalcOffset(size_t i, size_t j) const {
    return i * colsNum_ + j;
  }

  size_t GetRowsNum() const {
    return rowsNum_;
  }

  size_t GetColsNum() const {
    return colsNum_;
  }

  Row operator[](size_t rowNum) {
    return Row(rowNum, this);
  }

  ConstRow operator[](size_t rowNum) const {
    return ConstRow(rowNum, this);
  }

  Column operator()(size_t colNum) {
    return Column(colNum, this);
  }

  ConstColumn operator()(size_t colNum) const {
    return ConstColumn(colNum, this);
  }

  Matrix &operator=(const Matrix &rhs) ;

 private:
  // Константные методы.
  double &GetEl(size_t i, size_t j) const {
    return storage_[CalcOffset(i, j)];
  }

 private:
  void CheckIJ(size_t i, size_t j) const;

 public:
  static void Swap(Matrix &lhs, Matrix &rhs);

 private:
  double *storage_;
  size_t rowsNum_;
  size_t colsNum_;
};

#endif
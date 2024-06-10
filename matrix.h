#ifndef MYMATRIX_MATRIX_H
#define MYMATRIX_MATRIX_H

#include <cstdint>

class Matrix {
 public:
  // Типы, необходимость которых определена стандартом (псевдонимы).
  // Для C-массивов указатель на тип элемента этого массива является random access итератором.
  using value_type = double;
  using reference = double &;
  using const_reference = const double &; // или можно просто вернуть double.
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = double *;
  using const_pointer = const double *;

  // Можно было бы использовать просто double*.
  class iterator {
   public:
    iterator() : ptr_(nullptr) {}
    iterator(double *ptr) : ptr_(ptr) {}
   public:
    reference operator*() {
      return *ptr_;
    }
    reference operator*() const {
      return *ptr_;
    }
    iterator &operator++() {
      ++ptr_;
      return *this;
    }
    iterator &operator++(int) {
      iterator tmp(ptr_++);
      return tmp;
    }
    iterator &operator--() {
      --ptr_;
      return *this;
    }
    iterator &operator--(int) {
      iterator tmp(ptr_--);
      return tmp;
    }
    iterator &operator+=(size_type pos) {
      ptr_ += pos;
      return *this;
    }
    iterator &operator-=(size_type pos) {
      ptr_ -= pos;
      return *this;
    }
    iterator &operator=(const iterator &rhs) {
      ptr_ = rhs.ptr_;
      return *this;
    }
    bool operator==(const iterator &rhs) {
      return ptr_ == rhs.ptr_;
    }
    bool operator==(const iterator &rhs) const {
      return ptr_ == rhs.ptr_;
    }
    bool operator!=(const iterator &rhs) {
      return ptr_ != rhs.ptr_;
    }
    bool operator!=(const iterator &rhs) const {
      return ptr_ != rhs.ptr_;
    }
   private:
    double *ptr_;
  };
  class const_iterator {
   public:
    using reference = const double &;
    using size_type = std::size_t;

    const_iterator() : wrapped_it_() {}
    const_iterator(const double *ptr) : wrapped_it_(const_cast<double *>(ptr)) {}
    const_iterator(const iterator &it) : wrapped_it_(it) {}

    reference operator*() const {
      return *wrapped_it_;
    }
    const_iterator &operator++() {
      ++wrapped_it_;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp = *this;
      ++wrapped_it_;
      return tmp;
    }
    const_iterator &operator--() {
      --wrapped_it_;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator tmp = *this;
      --wrapped_it_;
      return tmp;
    }
    const_iterator &operator+=(size_type pos) {
      wrapped_it_ += pos;
      return *this;
    }
    const_iterator &operator-=(size_type pos) {
      wrapped_it_ -= pos;
      return *this;
    }
    const_iterator &operator=(const const_iterator &rhs) {
      if (this != &rhs) {
        wrapped_it_ = rhs.wrapped_it_;
      }
      return *this;
    }
    bool operator==(const const_iterator &rhs) const {
      return wrapped_it_ == rhs.wrapped_it_;
    }
    bool operator!=(const const_iterator &rhs) const {
      return wrapped_it_ != rhs.wrapped_it_;
    }

   private:
    iterator wrapped_it_;
  };
  class reverse_iterator {
   public:
    using reference = double &;
    using size_type = std::size_t;

    reverse_iterator() : wrapped_it_() {}
    reverse_iterator(double *ptr) : wrapped_it_(ptr) {}
    reverse_iterator(const iterator &it) : wrapped_it_(it) {}

    reference operator*() {
      iterator tmp = wrapped_it_;
      --tmp;
      return *tmp;
    }
    reverse_iterator &operator++() {
      --wrapped_it_;
      return *this;
    }
    reverse_iterator operator++(int) {
      reverse_iterator tmp = *this;
      --wrapped_it_;
      return tmp;
    }
    reverse_iterator &operator--() {
      ++wrapped_it_;
      return *this;
    }
    reverse_iterator operator--(int) {
      reverse_iterator tmp = *this;
      ++wrapped_it_;
      return tmp;
    }
    reverse_iterator &operator+=(size_type pos) {
      wrapped_it_ -= pos;
      return *this;
    }
    reverse_iterator &operator-=(size_type pos) {
      wrapped_it_ += pos;
      return *this;
    }
    reverse_iterator &operator=(const reverse_iterator &rhs) {
      if (this != &rhs) {
        wrapped_it_ = rhs.wrapped_it_;
      }
      return *this;
    }
    bool operator==(const reverse_iterator &rhs) const {
      return wrapped_it_ == rhs.wrapped_it_;
    }
    bool operator!=(const reverse_iterator &rhs) const {
      return wrapped_it_ != rhs.wrapped_it_;
    }

   private:
    iterator wrapped_it_;
  };
  class const_reverse_iterator {
   public:
    using reference = const double &;
    using size_type = std::size_t;

    const_reverse_iterator() : wrapped_it_() {}
    const_reverse_iterator(const double *ptr) : wrapped_it_(const_cast<double *>(ptr)) {}
    const_reverse_iterator(const reverse_iterator &rit) : wrapped_it_(rit) {}

    reference operator*() const {
      reverse_iterator tmp = wrapped_it_;
      --tmp;
      return *tmp;
    }
    const_reverse_iterator &operator++() {
      --wrapped_it_;
      return *this;
    }
    const_reverse_iterator operator++(int) {
      const_reverse_iterator tmp = *this;
      --wrapped_it_;
      return tmp;
    }
    const_reverse_iterator &operator--() {
      ++wrapped_it_;
      return *this;
    }
    const_reverse_iterator operator--(int) {
      const_reverse_iterator tmp = *this;
      ++wrapped_it_;
      return tmp;
    }
    const_reverse_iterator &operator+=(size_type pos) {
      wrapped_it_ -= pos;
      return *this;
    }
    const_reverse_iterator &operator-=(size_type pos) {
      wrapped_it_ += pos;
      return *this;
    }
    const_reverse_iterator &operator=(const const_reverse_iterator &rhs) {
      if (this != &rhs) {
        wrapped_it_ = rhs.wrapped_it_;
      }
      return *this;
    }
    bool operator==(const const_reverse_iterator &rhs) const {
      return wrapped_it_ == rhs.wrapped_it_;
    }
    bool operator!=(const const_reverse_iterator &rhs) const {
      return wrapped_it_ != rhs.wrapped_it_;
    }

   private:
    reverse_iterator wrapped_it_;
  };
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

    // Итераторы для строки.
   public:
    using iterator = double *;
    using const_iterator = const double *;

    class reverse_iterator {
     public:
      reverse_iterator(iterator it) : it_(it) {}
      reverse_iterator &operator++() {
        --it_;
        return *this;
      }
      reverse_iterator operator++(int) {
        reverse_iterator tmp = *this;
        --it_;
        return tmp;
      }
      reverse_iterator &operator--() {
        ++it_;
        return *this;
      }
      reverse_iterator operator--(int) {
        reverse_iterator tmp = *this;
        ++it_;
        return tmp;
      }
      double &operator*() { return *it_; }
      bool operator!=(const reverse_iterator &other) const { return it_ != other.it_; }
     private:
      iterator it_;
    };

    class const_reverse_iterator {
     public:
      const_reverse_iterator(const_iterator it) : it_(it) {}
      const_reverse_iterator &operator++() {
        --it_;
        return *this;
      }
      const_reverse_iterator operator++(int) {
        const_reverse_iterator tmp = *this;
        --it_;
        return tmp;
      }
      const_reverse_iterator &operator--() {
        ++it_;
        return *this;
      }
      const_reverse_iterator operator--(int) {
        const_reverse_iterator tmp = *this;
        ++it_;
        return tmp;
      }
      const double &operator*() const { return *it_; }
      bool operator!=(const const_reverse_iterator &other) const { return it_ != other.it_; }
     private:
      const_iterator it_;
    };

   public:
    iterator begin() const {
      return &matrix_->GetEl(rowNum_, 0);
    }
    const_iterator cbegin() const {
      return &matrix_->GetEl(rowNum_, 0);
    }
    reverse_iterator rbegin() const {
      return reverse_iterator(end());
    }
    const_reverse_iterator crbegin() const {
      return const_reverse_iterator(cend());
    }

    iterator end() const {
      return &matrix_->GetEl(rowNum_, 0) + matrix_->GetColsNum();
    }
    const_iterator cend() const {
      return &matrix_->GetEl(rowNum_, 0) + matrix_->GetColsNum();
    }
    reverse_iterator rend() const {
      return reverse_iterator(begin());
    }
    const_reverse_iterator crend() const {
      return const_reverse_iterator(cbegin());
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

   public:
    using const_iterator = const double *;

    class const_reverse_iterator {
     public:
      const_reverse_iterator(const_iterator it) : it_(it) {}
      const_reverse_iterator &operator++() {
        --it_;
        return *this;
      }
      const_reverse_iterator operator++(int) {
        const_reverse_iterator tmp = *this;
        --it_;
        return tmp;
      }
      const_reverse_iterator &operator--() {
        ++it_;
        return *this;
      }
      const_reverse_iterator operator--(int) {
        const_reverse_iterator tmp = *this;
        ++it_;
        return tmp;
      }
      const double &operator*() const { return *it_; }
      bool operator!=(const const_reverse_iterator &other) const { return it_ != other.it_; }
     private:
      const_iterator it_;
    };

   public:
    const_iterator cbegin() const {
      return &const_matrix_->GetEl(rowNum_, 0);
    }
    const_reverse_iterator crbegin() const {
      return const_reverse_iterator(cend());
    }

    const_iterator cend() const {
      return &const_matrix_->GetEl(rowNum_, 0) + const_matrix_->GetColsNum();
    }
    const_reverse_iterator crend() const {
      return const_reverse_iterator(cbegin());
    }

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

    class iterator {
     public:
      iterator(double *ptr, Matrix *matrix) : ptr_(ptr), matrix_(matrix) {}
      iterator &operator++() {
        ptr_ += matrix_->GetRowsNum();
        return *this;
      }
      iterator operator++(int) {
        iterator tmp = *this;
        ptr_ += matrix_->GetRowsNum();
        return tmp;
      }
      iterator &operator--() {
        ptr_ -= matrix_->GetRowsNum();
        return *this;
      }
      iterator operator--(int) {
        iterator tmp = *this;
        ptr_ -= matrix_->GetRowsNum();
        return tmp;
      }
      double &operator*() { return *ptr_; }
      bool operator!=(const iterator &other) const { return ptr_ != other.ptr_; }
     private:
      double *ptr_;
      Matrix *matrix_;
    };

    class const_iterator {
     public:
      const_iterator(const double *ptr, Matrix *matrix) : ptr_(ptr), matrix_(matrix) {}
      const_iterator &operator++() {
        ptr_ += matrix_->GetRowsNum();
        return *this;
      }
      const_iterator operator++(int) {
        const_iterator tmp = *this;
        ptr_ += matrix_->GetRowsNum();
        return tmp;
      }
      const_iterator &operator--() {
        ptr_ -= matrix_->GetRowsNum();
        return *this;
      }
      const_iterator operator--(int) {
        const_iterator tmp = *this;
        ptr_ -= matrix_->GetRowsNum();
        return tmp;
      }
      const double &operator*() const { return *ptr_; }
      bool operator!=(const const_iterator &other) const { return ptr_ != other.ptr_; }
     private:
      const double *ptr_;
      Matrix *matrix_;
    };

    class reverse_iterator {
     public:
      reverse_iterator(iterator it) : it_(it) {}
      reverse_iterator &operator++() {
        --it_;
        return *this;
      }
      reverse_iterator operator++(int) {
        reverse_iterator tmp = *this;
        --it_;
        return tmp;
      }
      reverse_iterator &operator--() {
        ++it_;
        return *this;
      }
      reverse_iterator operator--(int) {
        reverse_iterator tmp = *this;
        ++it_;
        return tmp;
      }
      double &operator*() { return *it_; }
      bool operator!=(const reverse_iterator &other) const { return it_ != other.it_; }
     private:
      iterator it_;
    };

    class const_reverse_iterator {
     public:
      const_reverse_iterator(const_iterator it) : it_(it) {}
      const_reverse_iterator &operator++() {
        --it_;
        return *this;
      }
      const_reverse_iterator operator++(int) {
        const_reverse_iterator tmp = *this;
        --it_;
        return tmp;
      }
      const_reverse_iterator &operator--() {
        ++it_;
        return *this;
      }
      const_reverse_iterator operator--(int) {
        const_reverse_iterator tmp = *this;
        ++it_;
        return tmp;
      }
      const double &operator*() const { return *it_; }
      bool operator!=(const const_reverse_iterator &other) const { return it_ != other.it_; }
     private:
      const_iterator it_;
    };

   public:
    iterator begin() const {
      return iterator(&matrix_->GetEl(0, colNum_), matrix_);
    }
    const_iterator cbegin() const {
      return const_iterator(&matrix_->GetEl(0, colNum_), matrix_);
    }
    reverse_iterator rbegin() const {
      return reverse_iterator(end());
    }
    const_reverse_iterator crbegin() const {
      return const_reverse_iterator(cend());
    }

    iterator end() const {
      return iterator(&matrix_->GetEl(0, colNum_) + matrix_->GetRowsNum(), matrix_);
    }
    const_iterator cend() const {
      return const_iterator(&matrix_->GetEl(0, colNum_) + matrix_->GetRowsNum(), matrix_);
    }
    reverse_iterator rend() const {
      return reverse_iterator(begin());
    }
    const_reverse_iterator crend() const {
      return const_reverse_iterator(cbegin());
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
    class const_iterator {
     public:
      const_iterator(const double *ptr, const Matrix *matrix) : ptr_(ptr), matrix_(matrix) {}
      const_iterator &operator++() {
        ptr_ += matrix_->GetRowsNum();
        return *this;
      }
      const_iterator operator++(int) {
        const_iterator tmp = *this;
        ptr_ += matrix_->GetRowsNum();
        return tmp;
      }
      const_iterator &operator--() {
        ptr_ -= matrix_->GetRowsNum();
        return *this;
      }
      const_iterator operator--(int) {
        const_iterator tmp = *this;
        ptr_ -= matrix_->GetRowsNum();
        return tmp;
      }
      const double &operator*() const { return *ptr_; }
      bool operator!=(const const_iterator &other) const { return ptr_ != other.ptr_; }
     private:
      const double *ptr_;
      const Matrix *matrix_;
    };

    class const_reverse_iterator {
     public:
      const_reverse_iterator(const_iterator it) : it_(it) {}
      const_reverse_iterator &operator++() {
        --it_;
        return *this;
      }
      const_reverse_iterator operator++(int) {
        const_reverse_iterator tmp = *this;
        --it_;
        return tmp;
      }
      const_reverse_iterator &operator--() {
        ++it_;
        return *this;
      }
      const_reverse_iterator operator--(int) {
        const_reverse_iterator tmp = *this;
        ++it_;
        return tmp;
      }
      const double &operator*() const { return *it_; }
      bool operator!=(const const_reverse_iterator &other) const { return it_ != other.it_; }
     private:
      const_iterator it_;
    };

   public:
    const_iterator cbegin() const {
      return const_iterator(&const_matrix_->GetEl(0, colNum_), const_matrix_);
    }
    const_reverse_iterator crbegin() const {
      return const_reverse_iterator(cend());
    }

    const_iterator cend() const {
      return const_iterator(&const_matrix_->GetEl(0, colNum_) + const_matrix_->GetRowsNum(), const_matrix_);
    }
    const_reverse_iterator crend() const {
      return const_reverse_iterator(cbegin());
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
  iterator begin() const {
    return iterator(storage_);
  }
  const_iterator cbegin() const {
    return const_iterator(storage_);
  }
  reverse_iterator rbegin() const {
    return reverse_iterator(storage_ + rowsNum_ * colsNum_);
  }
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(storage_ + rowsNum_ * colsNum_);
  }

  iterator end() const {
    return iterator(storage_ + rowsNum_ * colsNum_);
  }
  const_iterator cend() const {
    return const_iterator(storage_ + rowsNum_ * colsNum_);
  }
  reverse_iterator rend() const {
    return reverse_iterator(storage_);
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(storage_);
  }

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

  // CAO (Copy assigment operator).
  Matrix &operator=(const Matrix &rhs);
  // MAO (Move assigment operator).
  Matrix &operator=(Matrix &&victim);

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
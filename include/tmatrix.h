// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
      if (size <= 0 || size > MAX_VECTOR_SIZE) throw out_of_range("Incorrect size of vector!");
      this->pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      this->sz = v.sz;
      this->pMem = new T[sz]();
      for (int i = 0; i < sz; i++) this->pMem[i] = v.pMem[i];

  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      this->sz = v.sz;
      v.sz = 0;
      this->pMem = v.pMem;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] this->pMem;
  }

  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (&v == this) return *this;
      if (this->pMem != nullptr) delete[] this->pMem;
      this->sz = v.sz;
      this->pMem = new T[sz];
      for (int i = 0; i < sz; i++) this->pMem[i] = v.pMem[i];
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v) return *this;
      this->sz = v.sz;
      v.sz = 0;
      this->pMem = v.pMem;
      v.pMem = nullptr;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return this->pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return this->pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= this->sz) throw std::out_of_range("Index out of range!");
      return this->pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= this->sz) throw std::out_of_range("Index out of range!");
      return this->pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this->sz != v.sz) return false;
      for (int i = 0; i < this->sz; i++) { 
          if (this->pMem[i] != v.pMem[i]) return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(*this);
      for (int i = 0; i < tmp.sz; i++) tmp.pMem[i] += val;
      return tmp;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector tmp(*this);
      for (int i = 0; i < tmp.sz; i++) tmp.pMem[i] -= val;
      return tmp;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector tmp(*this);
      for (int i = 0; i < tmp.sz; i++) tmp.pMem[i] *= val;
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw invalid_argument("The sizes of the vectors don't equal");
      TDynamicVector tmp(*this);
      for (int i = 0; i < tmp.sz; i++) tmp.pMem[i] += v.pMem[i];
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw invalid_argument("The sizes of the vectors don't equal");
      TDynamicVector tmp(*this);
      for (int i = 0; i < tmp.sz; i++) tmp.pMem[i] -= v.pMem[i];
      return tmp;
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz) throw invalid_argument("The sizes of the vectors don't equal");
      T result = 0;
      for (int i = 0; i < this->sz; i++) result += this->pMem[i] * v.pMem[i];
      return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    std::cout << std::endl;
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s <= 0 || s > MAX_MATRIX_SIZE) throw out_of_range("Incorrect size of vector!");
      for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::size;

  // индексация
  using TDynamicVector<TDynamicVector<T>>::operator[];

  // индексация с контролем
  T& at(size_t i, size_t j) {
      if (i<0 || j<0 || i>=this->sz || j>=this->sz) throw std::out_of_range("Index out of range!");
      return this->pMem[i][j];
  }

  const T& at(size_t i, size_t j) const {
      if (i<0 || j<0 || i>=this->sz || j>=this->sz) throw std::out_of_range("Index out of range!");
      return this->pMem[i][j];
  }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<int>>::operator==(m);
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix result(this->sz);
      for (int i = 0; i < result.sz; i++) {
          result.pMem[i] = this->pMem[i] * val;
      }
      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (this->sz != v.size()) throw invalid_argument("The sizes of the vectors don't equal");
      TDynamicVector<T> result(sz);
      for (int i = 0; i < result.size(); i++) {
          result[i] = this->pMem[i] * v;
      }
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz) throw invalid_argument("The sizes of the matrix don't equal");
      TDynamicMatrix<T> result(this->sz);
      for (int i = 0; i < result.sz; i++) {
          result.pMem[i] = this->pMem[i] + m.pMem[i];
      }
      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz) throw invalid_argument("The sizes of the matrix don't equal");
      TDynamicMatrix<T> result(this->sz);
      for (int i = 0; i < result.sz; i++) {
          result.pMem[i] = this->pMem[i] - m.pMem[i];
      }
      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz) throw invalid_argument("The sizes of the matrix don't equal");
      TDynamicMatrix<T> result(this->sz);
      for (int i = 0; i < result.sz; i++) {
          for (int j = 0; j < result.sz; j++) {
              result.pMem[i][j] = 0;
          }
      }
      for (int i = 0; i < result.sz; i++) {
          for (int k = 0; k < result.sz; k++) {
              for (int j = 0; j < result.sz; j++) {
                  result.pMem[i][j] += this->pMem[i][k] * m.pMem[k][j];
              }
          }
      }

      return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++)
          istr >> m.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++)
          ostr << m.pMem[i];
      std::cout << std::endl;
      return ostr;
  }
};

#endif

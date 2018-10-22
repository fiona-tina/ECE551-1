#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
using namespace std;

template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  vector<vector<T> > rows;

 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix<T> & rhs);
  //~Matrix();
  Matrix<T> & operator=(const Matrix<T> & rhs);
  int getRows() const;
  int getColumns() const;
  const vector<T> & operator[](int index) const;
  vector<T> & operator[](int index);
  bool operator==(const Matrix<T> & rhs) const;
  Matrix<T> operator+(const Matrix<T> & rhs) const;
};
template<typename T>
Matrix<T>::Matrix() : numRows(0), numColumns(0) {}

template<typename T>
Matrix<T>::Matrix(int r, int c) :
    numRows(r),
    numColumns(c),
    rows(vector<vector<T> >(r, vector<T>(c))) {}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(rhs.rows) {}

//	Matrix::~Matrix() {
//		for (int i = 0; i < numRows; ++i) {
//			delete rows[i];
//		}
//		delete[] rows;
//	}
template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = rhs.rows;
  return *this;
}

template<typename T>
int Matrix<T>::getRows() const {
  return numRows;
}

template<typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}

template<typename T>
const vector<T> & Matrix<T>::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return rows[index];
}

template<typename T>
vector<T> & Matrix<T>::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  return numRows == rhs.numRows && numColumns == rhs.numColumns && rows == rhs.rows;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  Matrix<T> res(rhs.numRows, rhs.numColumns);
  typename vector<vector<T> >::iterator it;
  typename vector<vector<T> >::const_iterator x = rows.begin(), y = rhs.rows.begin();
  for (it = res.rows.begin(); it != res.rows.end(); ++it, ++x, ++y) {
    typename vector<T>::iterator it2 = it->begin();
    typename vector<T>::const_iterator x2 = x->begin(), y2 = y->begin();

    for (; it2 != it->end(); ++it2, ++x2, ++y2) {
      *it2 = *x2 + *y2;
    }
  }
  return res;
}
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); ++i) {
    if (i < rhs.getRows() - 1) {
      for (int j = 0; j < rhs.getColumns(); ++j) {
        if (j == 0) {
          cout << "{" << rhs[i][j];
          continue;
        }
        cout << ", " << rhs[i][j];
      }
      cout << "}" << endl;
    }

    else {
      for (int j = 0; j < rhs.getColumns(); ++j) {
        if (j == 0) {
          cout << "{" << rhs[i][j];
          continue;
        }
        cout << ", " << rhs[i][j];
      }
      cout << "}";
    }
  }
  s << " ]";
  return s;
}

#endif

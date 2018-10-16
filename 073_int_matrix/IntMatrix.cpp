#include "IntMatrix.h"

#include "IntArray.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new IntArray *[rhs.numRows]) {
  for (int i = 0; i < numRows; ++i) {
    rows[i] = new IntArray(numColumns);
    *rows[i] = *rhs.rows[i];
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; ++i) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    //std::cout << "fffffffffffff";
    IntArray ** temp = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; ++i) {
      temp[i] = new IntArray(numColumns);
      *temp[i] = *rhs.rows[i];
    }
    for (int i = 0; i < numRows; ++i) {
      delete rows[i];
    }
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;

    delete[] rows;
    rows = temp;
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numColumns != rhs.numColumns || numRows != rhs.numRows)
    return false;
  for (int i = 0; i < numRows; ++i) {
    if (*rows[i] != *rhs.rows[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix res(rhs.numRows, rhs.numColumns);

  for (int i = 0; i < numRows; ++i) {
    IntArray & rh1 = *rows[i];
    IntArray & rh2 = *rhs.rows[i];
    IntArray & lh = *res.rows[i];

    for (int j = 0; j < res.numColumns; ++j) {
      lh[j] = rh1[j] + rh2[j];
    }
  }
  return res;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); ++i) {
    if (i < rhs.getRows() - 1)
      s << rhs[i] << ", " << std::endl;
    else
      s << rhs[i];
  }
  s << " ]";
  return s;
}

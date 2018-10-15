#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() {
  numElements = 0;
  data = NULL;
}
IntArray::IntArray(int n) {
  numElements = n;
  data = new int[numElements];
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  int * tmp = new int[rhs.numElements];
  numElements = rhs.numElements;
  for (int i = 0; i < numElements; i++) {
    tmp[i] = rhs.data[i];
  }
  delete[] data;
  data = tmp;
  //delete[] tmp;
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index < numElements);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(index >= 0 && index < numElements);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements)
    return false;
  for (int i = 0; i < numElements; ++i) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (numElements != rhs.numElements)
    return true;
  else {
    for (int i = 0; i < numElements; ++i) {
      if (data[i] != rhs.data[i]) {
        return true;
      }
    }

    return false;
  }
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.numElements == 0)
    s << "{}";
  s << "{";
  for (int i = 0; i < rhs.numElements - 1; i++) {
    s << rhs.data[i] << ", ";
  }
  s << rhs.data[rhs.numElements - 1] << "}";
  return s;
}

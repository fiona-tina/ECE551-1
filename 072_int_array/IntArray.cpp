#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {}

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
  if (this != &rhs) {
    int * tmp = new int[rhs.numElements];

    for (int i = 0; i < rhs.numElements; i++) {
      tmp[i] = rhs.data[i];
    }
    delete[] data;
    data = tmp;
    numElements = rhs.numElements;
    //delete[] tmp;
  }
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
  int n = rhs.size();
  if (n == 0)
    s << "{}";
  s << "{";
  for (int i = 0; i < n - 1; i++) {
    s << rhs[i] << ", ";
  }
  s << rhs[n - 1] << "}";
  return s;
}

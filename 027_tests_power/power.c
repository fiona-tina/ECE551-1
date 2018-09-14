unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  else if (y == 1)
    return x;
  else {
    return power(x * x, y - 1);
  }
}

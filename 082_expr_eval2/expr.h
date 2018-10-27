#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Expression
{
 public:
  virtual string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression
{
 private:
  long num;

 public:
  explicit NumExpression(long x) : num(x){};
  virtual string toString() const {
    stringstream ss;
    ss << num;
    return ss.str();
  }
  virtual ~NumExpression(){};
};

class OpExpression : public Expression
{
 private:
  char ch;
  string left;
  string right;

 public:
  OpExpression(char ch, Expression * lhs, Expression * rhs) :
      ch(ch),
      left(lhs->toString()),
      right(rhs->toString()) {
    delete lhs;
    delete rhs;
  };
  virtual string toString() const {
    stringstream ss;
    ss << "(" << left << " " << ch << " " << right << ")";
    return ss.str();
  }
  ~OpExpression() {}
};

class PlusExpression : public OpExpression
{
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression('+', lhs, rhs){};
};

class MinusExpression : public OpExpression
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpExpression('-', lhs, rhs){};
};

class TimesExpression : public OpExpression
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpExpression('*', lhs, rhs){};
};

class DivExpression : public OpExpression
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OpExpression('/', lhs, rhs){};
};

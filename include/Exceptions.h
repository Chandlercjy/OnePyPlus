#include "OP_DECLARE.h"
#include <exception>

#pragma once

OP_NAMESPACE_START

using std::exception;

class BlowUpError : public exception {
  public:
    const char *what() const throw() {
        return "The Account is Blow Up!!";
    }
};

class BacktestFinished : public exception {
  public:
    const char *what() const throw() {
        return "Backtest Completed!";
    }
};

class OrderConflictError : public exception {
  public:
    const char *what() const throw() {
        return "$ and pct can't be set together";
    }
};

class PctRangeError : public exception {
  public:
    const char *what() const throw() {
        return "pct should be -1 < pct < 1";
    }
};

class QueueEmptyError : public exception {
  public:
    const char *what() const throw() {
        return "QueueEmptyError raised! Can't get from empty!";
    }
};

OP_NAMESPACE_END

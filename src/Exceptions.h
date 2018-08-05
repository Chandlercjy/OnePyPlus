#pragma once
#include <exception>

namespace except {

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
        return "OrderCoflictError raised!";
    }
};

class PctRangeError : public exception {
  public:
    const char *what() const throw() {
        return "PctRangeError raised!";
    }
};

class QueueEmptyError : public exception {
  public:
    const char *what() const throw() {
        return "QueueEmptyError raised! Can't get from empty!";
    }
};

} // namespace except

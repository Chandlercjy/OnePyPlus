
#include <exception>
#include <string>
#pragma once

using std::string;
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

} // namespace except

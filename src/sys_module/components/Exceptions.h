#include <exception>

namespace except {

using std::exception;

class BlowUpError : public exception {
  public:
    const char *what() const throw() {
        return "BlowUpError Raised!";
    }
    //BlowUpError() : exception("The Account is Blow Up!!\n"){};
};

//class BacktestFinished(Exception)
//pass

//class OrderConflictError(Exception):
//pass

//class PctRangeError(Exception):
//pass

} // namespace except

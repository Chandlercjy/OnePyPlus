#include <string>
#include <vector>

#pragma once

namespace op {
using std::string;
using std::vector;

class OnePiece;

OnePiece stock(const vector<string> &ticker_list,
               const string &frequency,
               const double initial_cash,
               const string &start,
               const string &end,
               const string &broker_name);

} // namespace op

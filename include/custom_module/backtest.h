#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class OnePiece;

OnePiece stock(const vector<string> &ticker_list,
               const string &frequency,
               const double initial_cash,
               const string &start,
               const string &end,
               const string &broker_name);

OnePiece forex(const vector<string> &ticker_list,
               const string &frequency,
               const double initial_cash,
               const string &start,
               const string &end,
               const string &broker_name);

OP_NAMESPACE_END

#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Counter {
  public:
    static int update_signal_id();
    static int update_signal_by_trigger_id();
    static int update_signal_cancel_id();
    static int update_order_id();
    static int update_mkt_id();

    //private:
    //static int signal_id;
    //static int signal_by_trigger_id;
    //static int signal_cancel_id;
    //static int order_id;
    //static int mkt_id;
};

//int Counter::signal_id = 1;
//int Counter::signal_by_trigger_id = 1;
//int Counter::signal_cancel_id = 1;
//int Counter::order_id = 1;
//int Counter::mkt_id = 1;

OP_NAMESPACE_END

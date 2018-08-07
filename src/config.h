#pragma once
#include "constants.h"
#include "environment.h"
#include <map>
#include <vector>

// 控制事件发生顺序

namespace config {

struct SingleLoop;
typedef std::vector<SingleLoop> LoopVector;

struct SingleLoop {
    SingleLoop(EVENT if_event, EVENT then_event, string module_name);
    const EVENT if_event;
    const EVENT then_event;
    string module_name;
    Environment *env;
    void run();
};

static LoopVector EVENT_LOOP = {SingleLoop(EVENT::Market_updated,
                                           EVENT::Data_cleaned,
                                           "cleaners"),

                                SingleLoop(EVENT::Data_cleaned,
                                           EVENT::Signal_generated,
                                           "strategies"),

                                SingleLoop(EVENT::Signal_generated,
                                           EVENT::Submit_order,
                                           "risk_managers"),

                                SingleLoop(EVENT::Submit_order,
                                           EVENT::Record_result,
                                           "brokers"),

                                SingleLoop(EVENT::Record_result,
                                           EVENT::None,
                                           "recorders")};
}; // namespace config

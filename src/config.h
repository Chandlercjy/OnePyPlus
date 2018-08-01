#pragma once
#include "constants.h"
#include "environment.h"
#include "sys_module/OnePyMetaBase.h"
#include <map>
#include <vector>

// 控制事件发生顺序

namespace config {

struct SingleLoop {
    SingleLoop(EVENT if_event, EVENT then_event,
               map<string, OnePyMetaBase *> *module_dict)
        : if_event(if_event),
          then_event(then_event),
          module_dict(module_dict){};
    const EVENT if_event;
    const EVENT then_event;
    map<string, OnePyMetaBase *> *module_dict;
};

typedef std::vector<SingleLoop> LoopVector;

static LoopVector EVENT_LOOP = {SingleLoop(EVENT::Market_updated,
                                           EVENT::Data_cleaned,
                                           &Environment::getInstance()->cleaners),

                                SingleLoop(EVENT::Data_cleaned,
                                           EVENT::Signal_generated,
                                           &Environment::getInstance()->strategies),

                                SingleLoop(EVENT::Signal_generated,
                                           EVENT::Submit_order,
                                           &Environment::getInstance()->risk_managers),

                                SingleLoop(EVENT::Submit_order,
                                           EVENT::Record_result,
                                           &Environment::getInstance()->brokers),

                                SingleLoop(EVENT::Record_result,
                                           EVENT::None,
                                           &Environment::getInstance()->recorders)};
}; // namespace config

#include "EventEngine.h"
#include "Exceptions.h"
#include "Constants.h"

OP_NAMESPACE_START

void EventEngine::put(EVENT event) {
    _core.push(event);
};

EVENT EventEngine::get(void) {
    _check_core_empty();
    EVENT result = _core.front();

    _core.pop();
    return result;
};

int EventEngine::size(void) const {
    return _core.size();
};

void EventEngine::_check_core_empty(void) const {
    if (_core.empty()) {
        throw QueueEmptyError();
    };
};

bool EventEngine::is_core_empty(void) const {
    return _core.empty() ? true : false;
};
OP_NAMESPACE_END



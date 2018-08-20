#include "../sys_module/models/BarBase.h"
#include "StockRecorder.h"

namespace sys {
StockRecorder::StockRecorder()
    : RecorderBase::RecorderBase() { save_to_env<StockRecorder>(this); };

std::shared_ptr<BarBase> StockRecorder::bar_class(const string &ticker,
                                                  const string &frequency) {
    return std::make_shared<BarBase>(ticker, frequency);
};

} // namespace sys

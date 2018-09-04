#include "OP_DECLARE.h"
#include "OrderStruct.h"

OP_NAMESPACE_START

void MarketOrderStruct::set_status(const OrderStatus &value) {
    _status = value;
}
void LimitOrderStruct::set_status(const OrderStatus &value) {
    _status = value;
}
void StopOrderStruct::set_status(const OrderStatus &value) {
    _status = value;
}
void TrailingStopOrderStruct::set_status(const OrderStatus &value) {
    _status = value;
}
void CancelOrderTSTStruct::set_status(const OrderStatus &value) {
    _status = value;
}
void CancelOrderPendingStruct::set_status(const OrderStatus &value) {
    _status = value;
}

OrderStatus MarketOrderStruct::get_status() { return _status; }
OrderStatus LimitOrderStruct::get_status() { return _status; }
OrderStatus StopOrderStruct::get_status() { return _status; }
OrderStatus TrailingStopOrderStruct::get_status() { return _status; }
OrderStatus CancelOrderTSTStruct::get_status() { return _status; }
OrderStatus CancelOrderPendingStruct::get_status() { return _status; }

OP_NAMESPACE_END

#include "Exceptions.h"

#include "Python.h"

#pragma once

OP_NAMESPACE_START

void translateBlowUpError(const BlowUpError &x) {
    PyErr_SetString(PyExc_UserWarning, "The Account is Blow Up!!");
};

void translateBacktestFinished(const BacktestFinished &x) {
    PyErr_SetString(PyExc_UserWarning, "Backtest Completed!");
};

void translateOrderConflictError(const OrderConflictError &x) {
    PyErr_SetString(PyExc_UserWarning, "$ and pct can't be set together");
};

void translatePctRangeError(const PctRangeError &x) {
    PyErr_SetString(PyExc_UserWarning, "pct should be -1 < pct < 1");
};

void translateQueueEmptyError(const QueueEmptyError &x) {
    PyErr_SetString(PyExc_UserWarning, "QueueEmptyError raised! Can't get from empty!");
};

OP_NAMESPACE_END

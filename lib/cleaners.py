from itertools import count

from numpy import array, isnan
from talib.abstract import Function

import OnePyPlus as op


class Talib(op.CleanerBase):
    counter = count(1)

    def __init__(self, ind: str, params: dict,
                 buffer_day: int, frequency: str) -> None:
        name = f"{ind}_{next(self.counter)}"
        self.indicator = Function(ind)
        self.indicator.set_parameters(params)
        rolling_window = self.indicator.lookback+1
        super().__init__(name, rolling_window, buffer_day, frequency)
        self.save_to_env(self)

        self.data = self.get_data()

    @staticmethod
    def _check_nan(value: float):
        if isnan(value):
            raise Exception(
                'rolling_window should be longer. Because nan is generated!')

    def _data_proxy(self, ticker: str) -> dict:
        key = f'{ticker}_{self.frequency}'

        return {'open': array(self.data[key].open),
                'high': array(self.data[key].high),
                'low': array(self.data[key].low),
                'close': array(self.data[key].close),
                'volume': array(self.data[key].volume)}

    def calculate(self, ticker: str) -> dict:
        self.indicator.set_input_arrays(self._data_proxy(ticker))
        value = list(self.indicator.outputs)

        if len(self.indicator.output_names) > 1:
            [self._check_nan(i[-1]) for i in value]

            return {k: v[-1]
                    for k, v in zip(self.indicator.output_names, value)}
        self._check_nan(value[-1])

        return value[-1]

import numpy as np
import pandas as pd
import statsmodels.api as sm

import OnePyPlus as op


def divide_data(array: pd.DataFrame, n: int):
    per_len = int(len(array) / n)

    return [array[i * per_len: (i + 1) * per_len]
            for i in range(n)]


def get_RS(array: pd.Series):
    mean = np.mean(array)
    Yt = np.cumsum((array - mean))
    Rt = np.max(Yt) - np.min(Yt)
    std = np.std(array)
    RS = Rt / std

    return RS


def get_hurst(array: pd.Series, fold_times: list = [1, 2, 4, 8, 16, 32]):
    datas = [divide_data(array, i) for i in fold_times]
    result = []

    for data in datas:
        single_avg_RS = np.mean([get_RS(i) for i in data])
        per_len = len(data[0])
        result.append((single_avg_RS, per_len))

    avg_RS_series = [i[0] for i in result]
    size_series = [i[1] for i in result]

    y = np.log10(avg_RS_series)
    x = np.log10(size_series)

    return sm.OLS(y, x).fit().params[0]


class Hurst(op.CleanerBase):

    def __init__(self, rolling_window=100, buffer_day=100, frequency="D"):
        super().__init__("Hurst", rolling_window, buffer_day, frequency)
        self.save_to_env(self)
        self.data = self.get_data()

    def calculate(self, ticker):
        array = np.array(self.data[f"{ticker}_{self.frequency}"].close)
        return get_hurst(array)

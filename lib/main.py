import OnePyPlus as op
import pandas as pd
from op_output import Output
from op_cleaners.Hurst import Hurst
from op_cleaners.Talib import Talib
from op_strategies.DualSMA import DualSMA

Frequency = "D"

class Luffy(op.StrategyBase):

    def __init__(self, name):
        super().__init__(name)
        self.save_to_env(self)
        self.env = self.get_env()
        self.hurst = Hurst(100, 140, Frequency).calculate
        self.sma1 = Talib("sma", dict(timeperiod=10), 15, Frequency).calculate
        self.sma2 = Talib("sma", dict(timeperiod=20), 29, Frequency).calculate

    def handle_bar(self):
        for ticker in self.env.tickers:
            if self.hurst(ticker) > 0.51:
                self.buy(20, ticker,3)
            elif self.hurst(ticker) < 0.48:
                self.sell(20, ticker)
            if self.hurst(ticker) > 0.51:
                self.short(20, ticker)
            elif self.hurst(ticker) < 0.48:
                self.cover(20, ticker)

        # print("SMA: ", self.sma("000001"))
        # print("Talib: ", self.sma1("000001"))
        # print(self.sma.data["000001_D"].date)
        # print(self.get_env().cleaners["SMA"])


luffy = Luffy("hahahaha")
# a = [DualSMA("TalibStrategy")]

go = op.OnePiece()

# go.load_csv("/Users/chandler/Documents/CLionProjects/OnePyPlus/data/",
# "000001", "000001")

START, END = '2017-05-25', '2018-03-09'
START, END = "2017-01-25", "2018-03-01"

# go.load_mongodb("000001_tushare", "000001")
# go.set_stock_backtest(100000, 0, 0.0016, 0.1)
# go.set_date(START, END, "D")

go.load_mongodb("EUR_USD_oanda", "EUR_USD")
go.set_forex_backtest(10000, 0.02)
go.set_date(START, END, Frequency)

go.sunny()



result = Output(go)

result.show()
result.plot("EUR_USD")
# print(plot.margin)

import OnePyPlus as op
from op_output import Output
from op_cleaners.Hurst import Hurst
from op_cleaners.Talib import Talib
from op_strategies.DualSMA import DualSMA


class Luffy(op.StrategyBase):

    def __init__(self, name):
        super().__init__(name)
        self.save_to_env(self)
        self.env = self.get_env()
        self.hurst = Hurst(100, 140, "M30").calculate
        self.sma1 = Talib("sma", dict(timeperiod=10), 1, "M30").calculate
        self.sma2 = Talib("sma", dict(timeperiod=20), 1, "M30").calculate

    def handle_bar(self):
        for ticker in self.env.tickers:
            if self.hurst(ticker) > 0.52:
                self.buy(20, ticker)
            elif self.hurst(ticker) < 0.48:
                self.sell(20, ticker)
            # if self.hurst(ticker) > 0.52:
                # self.short(20, ticker)
            # elif self.hurst(ticker) < 0.48:
                # self.cover(20, ticker)

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
START, END = "2018-01-25", "2018-02-01"

# go.load_mongodb("000001_tushare", "000001")
# go.set_stock_backtest(100000, 0, 0.0016, 0.1)
# go.set_date(START, END, "D")

go.load_mongodb("EUR_USD_oanda", "EUR_USD")
go.set_forex_backtest(100000, 0.02)
go.set_date(START, END, "M10")

go.sunny()


result = Output(go)

result.show()

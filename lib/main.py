import OnePyPlus as op
from op_strategies.DualSMA import DualSMA
from op_cleaners.Hurst import Hurst
from op_analysis import AmazingAnalysis


class Luffy(op.StrategyBase):

    def __init__(self, name):
        super().__init__(name)
        self.save_to_env(self)
        self.env = self.get_env()
        self.hurst = Hurst().calculate

    def handle_bar(self):
        for ticker in self.env.tickers:
            self.hurst(ticker)
            self.buy(20, ticker, 3, 0, 3, 0, 0, 0, 0, 0)
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
START, END = "2018-01-25", "2018-03-01"

# go.load_mongodb("000001_tushare", "000001")
# go.set_stock_backtest(100000, 0, 0.0016, 0.1)
# go.set_date(START, END, "D")

go.load_mongodb("EUR_USD_oanda", "EUR_USD")
go.set_forex_backtest(100000, 0.02)
go.set_date(START, END, "M30")

go.sunny()


result = AmazingAnalysis(go)

result.show()

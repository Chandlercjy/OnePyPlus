import OnePyPlus as op
from cleaners import Talib
from op_analysis import AmazingAnalysis


class Luffy(op.StrategyBase):

    def __init__(self, name):
        super().__init__(name)
        self.save_to_env(self)
        self.sma = SMA().calculate
        self.sma1 = Talib(ind='sma',
                          params=dict(timeperiod=10),
                          buffer_day=15,
                          frequency="D").calculate
        self.env = self.get_env()

    def handle_bar(self):
        for ticker in self.env.tickers:
            self.buy(20, ticker, 3, 0, 3, 0, 0, 0, 0, 0)
        # print("SMA: ", self.sma("000001"))
        # print("Talib: ", self.sma1("000001"))
        # print(self.sma.data["000001_D"].date)
        # print(self.get_env().cleaners["SMA"])


class SMA(op.CleanerBase):

    def __init__(self, rolling_window=10, buffer_day=14, frequency="D"):
        super().__init__("SMA", rolling_window, buffer_day, frequency)
        self.save_to_env(self)
        self.data = self.get_data()
        self.rolling_window = rolling_window

    def calculate(self, ticker):
        return sum(self.data[f"{ticker}_{self.frequency}"].close)/self.rolling_window


class TalibStrategy(op.StrategyBase):

    def __init__(self, name):
        super().__init__(name)
        self.save_to_env(self)
        self.sma1 = Talib(ind='sma',
                          params=dict(timeperiod=2),
                          buffer_day=30,
                          frequency="D").calculate
        self.sma2 = Talib(ind='sma',
                          params=dict(timeperiod=3),
                          buffer_day=40,
                          frequency="D").calculate

        self.params = dict(
            position=10,
            takeprofit=15,
            stoploss=10,
        )

        self.env = self.get_env()

    def handle_bar(self):
        for ticker in self.env.tickers:
            position = self.params['position']
            takeprofit = self.params['takeprofit']
            stoploss = self.params['position']

            if self.sma1(ticker) > self.sma2(ticker):
                print(self.sma1(ticker))
                self.buy(position, ticker,
                         takeprofit=takeprofit,
                         takeprofit_pct=0,
                         stoploss=stoploss)
            else:
                self.sell(position, ticker)


luffy = Luffy("hahahaha")
# a = [TalibStrategy("TalibStrategy")]

go = op.OnePiece()

# go.load_csv("/Users/chandler/Documents/CLionProjects/OnePyPlus/data/",
# "000001", "000001")

START, END = '2017-05-25', '2018-03-09'
START, END = "2018-01-25", "2018-04-01"

# go.load_mongodb("000001_tushare", "000001")
# go.set_stock_backtest(100000, 0, 0.0016, 0.1)
# go.set_date(START, END, "D")

go.load_mongodb("EUR_USD_oanda", "EUR_USD")
go.set_forex_backtest(100000, 0.02)
go.set_date(START, END, "D")

go.sunny()


result = AmazingAnalysis(go)

result.show()

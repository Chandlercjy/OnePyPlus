
import OnePyPlus as op
from op_cleaners.Talib import Talib

class DualSMA(op.StrategyBase):

    def __init__(self, name):
        super().__init__(name)
        self.save_to_env(self)
        self.env = self.get_env()
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

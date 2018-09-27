import OnePyPlus as op

class SMA(op.CleanerBase):

    def __init__(self, rolling_window=10, buffer_day=14, frequency="D"):
        super().__init__("SMA", rolling_window, buffer_day, frequency)
        self.save_to_env(self)
        self.data = self.get_data()
        self.rolling_window = rolling_window

    def calculate(self, ticker):
        return sum(self.data[f"{ticker}_{self.frequency}"].close)/self.rolling_window


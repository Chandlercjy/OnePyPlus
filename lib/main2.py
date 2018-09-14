import OnePyPlus as op
from event_engine import EVENT, EventEngine


class Environment:
    cleaners: dict = {}
    strategies: dict = {}
    risk_managers: dict = {}


class Luffy(op.StrategyBase):

    def __init__(self, name):
        super().__init__(name)
        self.save_to_env(self)

    def handle_bar(self):
        # self.buy(20, "000001", 0, 0.1, 0, 0, 0, 0, 0, 0)
        self.buy(ticker="000001", size=20, takeprofit=0.03)
        # print(66)
        # self.buy(20, "000001", 0, 0.01, 0, 0, 0, 0, 0, 0.01)
        # self.short(5, "000001",0,0.1,0,0,0,0.01,0,0)
        # self.print_position()

    # def run(self):
        # self.handle_bar()


luffy = Luffy("hahahaha")
# op.save_strategy(luffy)

go = op.OnePiece()
op.CsvReader("/Users/chandler/Documents/CLionProjects/OnePyPlus/data/",
             "000001", "000001")

go.set_stock_backtest(100000, 0, 0.0016, 0.1)

go.set_date("2017-02-05", "2017-04-01", "D", "A_shares")


go.sunny(True)

# op.print_balance()
# print(luffy.env)
env = luffy.get_env()
print(env.fromdate)
print(list(env.tickers))
print(list(env.suspended_tickers_record))
# env.fromdate = 1
# print(env.sys_date)
# # op.Luffy()
# # a = Luffy("Luffy")
# # go.sunny()
# # a.print_balance()

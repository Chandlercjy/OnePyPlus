import OnePyPlus as op
import pandas as pd
from op_analysis import AmazingAnalysis


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
        # self.buy(20, "000001", 0, 0.03, 0, 0, 0, 0, 0, 0)
        # self.buy(20, "000001", 0, 0.01, 0, 0, 0, 0, 0, 0.01)
        self.short(20, "000001", 0, 0.01, 0, 0, 0, 0, 0, 0.01)
        # self.buy(ticker="000001", size=20, takeprofit=0,takeprofit_pct=0.01)
        # print(66)
        # self.buy(20, "000001", 0, 0.01, 0, 0, 0, 0, 0, 0.01)
        # self.short(5, "000001",0,0.1,0,0,0,0.01,0,0)
        # self.print_position()

    # def run(self):
        # self.handle_bar()


luffy = Luffy("hahahaha")
# op.save_strategy(luffy)

go = op.OnePiece()

# op.CsvReader("/Users/chandler/Documents/CLionProjects/OnePyPlus/data/",
             # "000001", "000001")

op.MongodbReader("000001_tushare","000001")

go.set_stock_backtest(100000, 0, 0.0016, 0.1)

go.set_date("2018-01-25", "2018-04-01", "D", "A_shares")


go.sunny(True)

def dict_to_table(dict_data):
    for key, value in dict_data.items():
        if not isinstance(value, str):
            dict_data[key] = str(value)

    max_key_len = max([len(i) for i in dict_data])+1
    max_value_len = max([len(i) for i in dict_data.values()])+1
    total_len = max_key_len+max_value_len+3

    print(f'+{total_len*"-"}+')

    for key, value in dict_data.items():
        print(f'|{key.ljust(max_key_len)} | {value.rjust(max_value_len)}|')
    print(f'+{total_len*"-"}+')

# op.print_balance()
# print(luffy.env)
env = luffy.get_env()
# print(env.fromdate)
# print(list(env.tickers))
# print(list(env.suspended_tickers_record))
# print(go.avg_price)
analysis = AmazingAnalysis(go)
dict_to_table(analysis.general_summary())

print(analysis.detail_summary())
# env.fromdate = 1
# print(env.sys_date)
# # op.Luffy()
# # a = Luffy("Luffy")
# # go.sunny()
# # a.print_balance()

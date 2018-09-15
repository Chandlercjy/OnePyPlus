import OnePyPlus as op
from op_analysis import AmazingAnalysis


class Luffy(op.StrategyBase):

    def __init__(self, name):
        super().__init__(name)
        self.save_to_env(self)

    def handle_bar(self):
        self.buy(20, "000001", 3, 0, 3, 0, 0, 0, 0, 0)


luffy = Luffy("hahahaha")

go = op.OnePiece()

# go.load_csv("/Users/chandler/Documents/CLionProjects/OnePyPlus/data/",
             # "000001", "000001")

go.load_mongodb("000001_tushare","000001")
go.set_stock_backtest(100000, 0, 0.0016, 0.1)
go.set_date("2018-01-25", "2018-04-01", "D", "A_shares")

go.sunny(True)



result = AmazingAnalysis(go)
result.show()


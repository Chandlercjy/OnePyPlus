
import OnePyPlus as op
from event_engine import EVENT, EventEngine


class Environment:
    cleaners: dict = {}
    strategies: dict = {}
    risk_managers: dict = {}


class OnePiece(op.OnePiece):
    env = Environment

    def __init__(self):
        super().__init__()
        self.event_engine = EventEngine()

    def sunny(self):
        self._cpp_initialize_trading_system()

        while True:
            try:
                if self._cpp_event_engine_is_empty() and self.event_engine.is_empty():
                    self._cpp_market_maker_update_market()
                    self._cpp_pending_order_checker_run()
                else:
                    if not self._cpp_event_engine_is_empty():
                        cur_event = self._cpp_get_cur_event()
                    else:
                        cur_event = self.event_engine.get()
                    # print(cur_event)
                    self._run_event_loop(cur_event)

            except UserWarning as e:
                print(e)

                # if summary:
                # print("\n")
                # self.output.summary()

                break

    def _run_event_loop(self, cur_event: str):

        if cur_event == "Market_updated":
            self._run_cleaners()
            self.event_engine.put(EVENT.Data_cleaned)
        elif cur_event == EVENT.Data_cleaned:
            self._run_strategies()
            self.event_engine.put(EVENT.Signal_generated)
        elif cur_event == EVENT.Signal_generated:
            self._run_risk_managers()
            self.event_engine.put(EVENT.Submit_order)
        elif cur_event == EVENT.Submit_order:
            self._cpp_run_brokers()
            self.event_engine.put(EVENT.Record_result)
        elif cur_event == EVENT.Record_result:
            self._cpp_run_recorders()

    def _run_cleaners(self):
        pass

    def _run_strategies(self):
        [i.run() for i in self.env.strategies.values()]

    def _run_risk_managers(self):
        pass


class Luffy(op.StrategyBase):
    env = Environment

    def __init__(self, name):
        super().__init__(name)
        self.env.strategies[name] = self

    def handle_bar(self):
        self.buy(20, "000001", 0, 0.1, 0, 0, 0, 0, 0, 0)
        self.buy(20, "000001", 0, 0.01, 0, 0, 0, 0, 0, 0.01)
        # self.short(5, "000001",0,0.1,0,0,0,0.01,0,0)
        # self.print_balance()
        # self.print_position()

    def run(self):
        self.handle_bar()


go = OnePiece()
go.load_csv_reader("/Users/chandler/Documents/CLionProjects/OnePyPlus/data/",
                   "000001", "000001")
go.set_stock_backtest(100000, 0, 0.0016, 0.1)

go.set_date("2012-02-05", "2017-04-01", "D", "A_shares")
# op.Luffy()
a = Luffy("Luffy")
go.sunny()
a.print_balance()

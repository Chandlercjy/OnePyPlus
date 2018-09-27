import matplotlib.pyplot as plt
import matplotlib.style as style
import pandas as pd
import statsmodels.api as sm
from matplotlib.widgets import MultiCursor

from op_analysis.useful_func import (get_drawdown_df, to_dataframe,
                                     to_dataframe_list)


def sum_of_dataframe_list(data: dict) ->pd.DataFrame:
    dataframe_list = []

    for value in data.values():
        if len(value) == 1:
            continue
        df = pd.DataFrame(value)
        df = df[~df.date.duplicated(keep='last')]
        df.set_index('date', inplace=True)
        df.index = pd.to_datetime(df.index)
        dataframe_list.append(df)
    result = sum(dataframe_list)

    return result


class Matplotlib:

    def __init__(self, go):
        self.go = go
        self.positions = to_dataframe_list(go.tickers,
                                           "position", go.position)
        self.holding_pnl = to_dataframe_list(go.tickers,
                                             "holding_pnl", go.holding_pnl)
        self.commission = to_dataframe_list(go.tickers,
                                            "commission", go.commission)
        self.margin = to_dataframe_list(go.tickers,
                                        "margin", go.margin)
        self.balance = to_dataframe(go.balance, "balance")
        self.cash = to_dataframe(go.cash, "cash")

    @property
    def realized_pnl(self):
        trade_log = pd.DataFrame(self.go.trade_log)
        trade_log.dropna(inplace=True)
        trade_log = trade_log.loc[trade_log['exit_type'] != ""]

        if trade_log.shape[0] == 0:
            return pd.DataFrame([0])
        df = trade_log[['exit_date', 're_pnl']].copy()
        df.rename(columns=dict(exit_date='date'), inplace=True)
        df.set_index('date', drop=True, inplace=True)
        df.index = pd.to_datetime(df.index)

        return df

    @property
    def returns(self):
        returns_df = self.balance.pct_change().dropna()
        returns_df.columns = ['returns']

        return returns_df

    def setting(self):
        style.use('ggplot')
        plt.rcParams['lines.linewidth'] = 1.4
        plt.rcParams['figure.figsize'] = 6, 10

    def close(self, ticker):
        df = pd.DataFrame(self.go.ohlc(ticker))
        df.set_index('date', inplace=True)
        df.index = pd.to_datetime(df.index)
        df = df[['close']]
        df.rename(columns=dict(close=ticker), inplace=True)

        return df

    def plot(self, ticker):
        self.setting()

        fig = plt.figure(tight_layout=True)
        ax1 = fig.add_subplot(5, 2, 1)
        ax2 = fig.add_subplot(5, 2, 2)
        ax3 = fig.add_subplot(5, 2, 3)
        ax4 = fig.add_subplot(5, 2, 4)
        ax5 = fig.add_subplot(5, 2, 5)
        ax6 = fig.add_subplot(5, 2, 6)
        ax7 = fig.add_subplot(5, 2, 7)
        ax8 = fig.add_subplot(5, 2, 8)
        ax9 = fig.add_subplot(5, 2, 9)
        ax10 = fig.add_subplot(5, 2, 10)

        # 左边
        self.close(ticker).plot(ax=ax1, sharex=ax5)

        self.balance.plot(ax=ax3)
        self.cash.plot(ax=ax5, sharex=ax5)
        get_drawdown_df(self.balance).plot(ax=ax9, sharex=ax5)

        holding_pnl = sum_of_dataframe_list(self.go.holding_pnl)

        holding_pnl.rename(columns=dict(
            value=f'holding_pnl'), inplace=True)
        holding_pnl.plot(ax=ax7, sharex=ax5)
        # for i in self.holding_pnl_df:
        # i.plot(ax=ax7, sharex=ax5)

        # 右边

        market_value = sum_of_dataframe_list(self.go.market_value)

        market_value.rename(columns=dict(
            value=f'market_value'), inplace=True)
        market_value.plot(ax=ax2, sharex=ax5)

        margin = sum_of_dataframe_list(self.go.margin)

        margin.rename(columns=dict(
            value=f'margin'), inplace=True)
        margin.plot(ax=ax4, sharex=ax5)

        # for i in self.positions_df:
        # i.plot(ax=ax2, sharex=ax5)

        # for i in self.margin_df:
        # i.plot(ax=ax4, sharex=ax5)

        self.realized_pnl.plot(ax=ax6, sharex=ax5, kind='bar')

        sm.qqplot(self.returns['returns'],
                  dist='norm', line='s', ax=ax8, marker='.')
        self.returns[self.returns != 0].hist(bins=100, ax=ax10)

        MultiCursor(fig.canvas, (ax1,  ax3,  ax5,
                                 ax7,  ax9), color='r', lw=1)
        plt.show()

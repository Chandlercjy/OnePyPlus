import arrow
import numpy as np
import pandas as pd

TRADING_DAYS_PER_YEAR = 252
RISK_FREE = 0


def get_sharpe_ratio(balance):
    data = balance.pct_change().dropna()
    ratio = (np.sqrt(TRADING_DAYS_PER_YEAR) *
             ((np.mean(data))-RISK_FREE) / np.std(data))

    return ratio[0]


def get_sortino_ratio(balance):
    data = balance.pct_change().dropna()
    negative = data[data < 0].dropna().values
    ratio = np.sqrt(TRADING_DAYS_PER_YEAR) * \
        (np.mean(data)-RISK_FREE) / np.std(negative)

    return ratio[0]


def get_drawdown_df(balance):
    drawdown_df = balance/balance.expanding().max()-1
    drawdown_df[np.isinf(drawdown_df)] = 0
    drawdown_df.rename(columns=dict(balance='drawdown'), inplace=True)

    return -drawdown_df


def get_max_drawdown(balance):
    return get_drawdown_df(balance).max().values[0]


def get_max_drawdown_date(balance):
    df = get_drawdown_df(balance)
    max_drawdown = get_max_drawdown(balance)
    date = df[df.drawdown == max_drawdown].index[0]

    return arrow.get(date).format('YYYY-MM-DD')


def get_max_duration_in_drawdown(balance):
    max_balance = balance.expanding().max()
    diff = max_balance.shift(-1) - max_balance
    diff.dropna(inplace=True)

    count = 0
    count_list = []

    for i in diff.values:
        if i <= 0:
            count += 1
        else:
            count_list.append(count)
            count = 0
    count_list.append(count)

    return max(count_list)


def to_dataframe(data, name) -> pd.DataFrame:
    dataframe = pd.DataFrame(data)
    dataframe.rename(columns=dict(value=name), inplace=True)
    dataframe.set_index('date', inplace=True)
    dataframe.index = pd.to_datetime(dataframe.index)
    result = dataframe[~dataframe.index.duplicated(keep='last')]

    first = dataframe.ix[: 1]
    result = pd.concat([first, result])
    result.sort_index(inplace=True)

    return result


def to_dataframe_list(tickers, name, series) -> list:
    dataframe_list = []

    for ticker in tickers:
        long_df = pd.DataFrame(series[f'{ticker}_long'])
        short_df = pd.DataFrame(series[f'{ticker}_short'])
        long_df.rename(columns=dict(
            value=f'{name}_{ticker}_long'), inplace=True)
        short_df.rename(columns=dict(
            value=f'{name}_{ticker}_short'), inplace=True)

        long_df = long_df[~long_df.date.duplicated(keep='last')]
        short_df = short_df[~short_df.date.duplicated(keep='last')]

        long_df.set_index('date', inplace=True)
        long_df.index = pd.to_datetime(long_df.index)

        short_df.set_index('date', inplace=True)
        short_df.index = pd.to_datetime(short_df.index)

        dataframe_list.append(long_df)
        dataframe_list.append(short_df)

    return dataframe_list


def get_total_value(data: list) -> float:
    total = 0

    for data_list in data.values():
        per_dict = data_list[-1]
        total += per_dict['value']

    return total

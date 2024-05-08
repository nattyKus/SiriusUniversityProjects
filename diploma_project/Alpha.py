import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import rankdata


class Alpha():
    '''Class for alpha operations'''

    def __init__(self, weights_path, close_path, vwap_path):
        self.weights = pd.read_parquet(weights_path)
        self.close_df = pd.read_parquet(close_path)
        self.vwap_df = pd.read_parquet(vwap_path)
        self.shape = self.weights.shape
        self.metrics = None
    

    def neutralize(self):
        self.weights = self.weights.sub(self.weights.mean(axis=1), axis=0)

    def scale(self):
        self.weights = self.weights.div(self.weights.abs().sum(axis=1), axis=0)

    def truncate(self, max_weight=0.03):
        # assumption : weights is scaled to 1
        self.weights = self.weights.clip(-max_weight, max_weight)

    def truncate_and_normalize(self, max_weight=0.03):
        self.neutralize()
        self.scale()
        for _ in range(10):
            self.truncate(max_weight)
            self.neutralize()
            self.scale()

    def rank(self):
        self.weights = (rankdata(self.weights, axis=1) - 1) / (self.shape[1] - 1)

    def decay(self, n):
        self.weights = self.weights.ewm(com=n).mean()

    def backtest(self, delay=0, display=False, label=None):
        if delay == 0:
            returns = self.close_df.pct_change(fill_method=None).clip(-0.5, 1.0)

            pnl = (self.weights.shift() * returns).sum(axis=1)
            daily_tvr = (
                (self.weights.fillna(0) - self.weights.shift().fillna(0) * (1 + returns.fillna(0)))
                .abs()
                .sum(axis=1)
            ).resample("1d").sum()

        elif delay == 1:
            returns = self.vwap_df.pct_change(fill_method=None).clip(-0.5, 1.0)

            pnl = (self.weights.shift(2) * returns).sum(axis=1)
            daily_tvr = (
                (self.weights.shift().fillna(0) - self.weights.shift(2).fillna(0) * (1 + returns.fillna(0)))
                .abs()
                .sum(axis=1)
            ).resample("1d").sum()

        daily_pnl = pnl.resample("1d").sum()
        cum_daily_pnl = daily_pnl.cumsum()

        annual_sharpe = np.sqrt(365) * daily_pnl.mean() / daily_pnl.std()
        annual_return = daily_pnl.mean() * 365

        drawdown = cum_daily_pnl - cum_daily_pnl.cummax()
        max_drawdown = drawdown.min()
        margin = returns.sum(axis=1).mean() / daily_tvr.mean()

        self.metrics = dict(
            daily_pnl=daily_pnl,
            annual_sharpe=annual_sharpe, 
            daily_tvr=daily_tvr, 
            annual_return=annual_return,
            max_drawdown=max_drawdown, 
            margin=margin)
        
        if display:
            plt.plot(daily_pnl.index, daily_pnl.cumsum(), label=label)

            print(label)
            print()
            print("Annualized Sharpe Ratio = {}".format(annual_sharpe))
            print("Daily tvr = {}%".format(np.round(100 * daily_tvr.mean(), 3)))
            print("Annual return = {}%".format(np.round(annual_return, 3)))
            print("Max Drawdown = {}%".format(np.round(max_drawdown, 3)))
            print("Margin = {}%".format(np.round(margin, 3)))
            print()

    def set_reversion_window(self, window):
        self.weights = self.weights.rolling(window).sum()
        
    def truncate_by_date_period(self, date_period):
        self.weights = self.weights.loc[date_period[0]: date_period[1]]
        self.close_df = self.close_df.loc[date_period[0]: date_period[1]]
        self.vwap_df = self.vwap_df.loc[date_period[0]: date_period[1]]

    def save_to_local(self, path):
        self.weights.to_parquet(path, compression='gzip')

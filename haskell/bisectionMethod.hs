module Demo where
import Prelude

metBisection :: Double -> Double -> Double -> (Double -> Double) -> [(Double, Double)]
metBisection xn xk eps f = helper_metBisection xn xk
  where 
      helper_metBisection xn xk
        | (f xn * f xk) > 0 = error "function is not crossing 0"
        | f xn == 0 = [(xn, 0)]
        | f xk == 0 = [(xk, 0)]
        | xk - xn > eps && (f xn * f xi) < 0 = res : helper_metBisection xn xi
        | xk - xn > eps && (f xi * f xk) < 0 = res : helper_metBisection xi xk
        | otherwise = [res]
        where
          xi = xn + (xk - xn) / 2
          res = (xi, xk - xn)
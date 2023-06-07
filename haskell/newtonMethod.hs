module Demo where
import Prelude

metNewton f x0 eps | abs (x0 - newx) < eps = [res]
                   | otherwise = res : metNewton f newx eps
    where 
        newx = newX f f1 x0
        res = (newx, abs (x0 - newx))
        f1 f x0 = (f (x0 + 0.1) - f x0) / 0.1
        newX f f1 x0 = x0 - f x0 / f1 f x0
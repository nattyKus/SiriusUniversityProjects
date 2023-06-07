---- Currency
data Currency = RUB | USD | EUR deriving (Show, Eq)
test11 = RUB == USD

---- Price
data Price = Px' {getCur::Currency, getPx::Double} deriving (Eq)
  
addPrice p1 p2 
    | getCur p1 == getCur p2 = Px' (getCur p1) (getPx p1 + getPx p2)
    | otherwise = undefined

---- Price''
newtype Price'' a = Px'' Double deriving (Eq, Show)
data Rub
data Usd

addPrice'' :: Price'' a -> Price'' a -> Price'' a
addPrice'' (Px'' d1) (Px'' d2) = Px'' (d1 + d2)

---- Px
data Px = PxRub Double | PxUsd Double deriving (Eq)

addPx :: Px -> Px -> Px
addPx (PxRub d1) (PxRub d2) = PxRub (d1+d2)
addPx (PxUsd d1) (PxUsd d2) = PxUsd (d1+d2)

--------- лаб2 задание 1: ---------

-- для типа Price сделайте
-- 1) функции вычитания subPrice, умножения на число mulPrice
subPrice :: Price -> Price -> Price
subPrice p1 p2 
    | getCur p1 == getCur p2 = Px' (getCur p1) (getPx p1 - getPx p2)
    | otherwise = undefined

mulPrice :: Price -> Double -> Price
mulPrice p1 k = Px' (getCur p1) (getPx p1 * k)

-- 2**) метод show с результатом в виде `2.5 руб`, `3 $` 
instance Show Price where
    show p = show (getPx p) ++ " " ++ helper p
      where helper p 
             | getCur p == RUB = "руб."
             | getCur p == USD = "$"
             | otherwise = undefined

-- 3*) функцию addPriceM -> Price -> Price -> Maybe ...
--newtype Price' a = Px' Double deriving (Eq, Show)

addPriceM :: Price -> Price -> Maybe Price
addPriceM p1 p2 
    | getCur p1 == getCur p2 = Just (Px' (getCur p1) (getPx p1 + getPx p2))
    | otherwise = Nothing

-- 4*) функцию addPriceE -> Price -> Price -> Either ...

addPriceE :: Price -> Price -> Either String Price
addPriceE p1 p2 
    | getCur p1 == getCur p2 = Right (Px' (getCur p1) ( getPx p1 + getPx p2 ))
    | otherwise = Left "Error : diff cur"

-- 5) напишите примеры (что работает и что не работает)

-- p11 = Px' RUB 2.5    p11       Output: 2.5 руб.
-- p12 = Px' RUB 3      p12       Output: 3.0 руб.
-- p13 = Px' USD 2.0    p13       Output: 2.0 $
-- addPrice p11 p12               Output: 5.5 руб.
-- addPrice p11 p13               Output: error, undefined
-- subPrice p11 p12               Output: -0.5 руб.
-- subPrice p11 p13               Output: error, undefined
-- mulPrice p11 4                 Output: 10.0 руб.
-- mulPrice p13 4                 Output: 8.0 $


--------- лаб2 задание2: ---------

-- 1) функции subPrice'', mulPrice''

subPrice'' :: Price'' a -> Price'' a -> Price'' a
subPrice'' (Px'' d1) (Px'' d2) = Px'' (d1-d2)

mulPrice'' :: Price'' a -> Double -> Price'' a
mulPrice'' (Px'' d1) k = Px'' (d1 * k)

-- 2) напишите примеры (что работает и что не работает)

-- p21 = Px'' 3 :: Price'' Rub
-- p22 = Px'' 4 :: Price'' Rub
-- p23 = Px'' 4 :: Price'' Usd
-- addPrice'' p21 p22     Output: Px'' 7.0
-- addPrice'' p21 p23     Output: error
-- mulPrice'' p21 3       Output: Px'' 9.0


--------- лаб2 задание3: ---------

--- для типа Px сделайте
-- 1) функции subPx, mulPx

subPx :: Px -> Px -> Px
subPx (PxRub d1) (PxRub d2) = PxRub (d1-d2)
subPx (PxUsd d1) (PxUsd d2) = PxUsd (d1-d2)

mulPx :: Px -> Double -> Px
mulPx (PxRub d1) k = PxRub (d1*k)
mulPx (PxUsd d1) k = PxUsd (d1*k)

-- 2*) добавьте распечатку единиц измерения (т.е. 2.5 руб., 3 $)

instance Show Px where
    show (PxRub p) = show p ++ " " ++ "руб."
    show (PxUsd p) = show p ++ " " ++ "$"

-- 3) напишите примеры (что работает и что не работает)

-- p31 = PxRub 2      p31     Output: 2.0 руб.
-- p32 = PxRub 3
-- p33 = PxUsd 3
-- addPx p31 p32              Output: 5.0 руб.
-- subPx p31 p32              Output: -1.0 руб.
-- subPx p31 p33              Output: Exception
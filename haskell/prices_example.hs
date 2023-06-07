-- обозначения комментариев
---- ###     - разделы кода
--           - комментрарии
----         - тесты, TODO
---          - строки, которые запускать в GHCi, для проверки 
--- Output:  - то, что выводится на экран


---- ###1 Price0
-- newtype Price0 = Px0 Double deriving (Read, Show) -- ver1
data Price0 = Px0 Double deriving (Read, Show) -- ver2
-- px2double :: Price -> Double
px2double (Px0 d) = d
----test1
p1 = Px0 2
--- p1 -- Output: Px0 2.0
m1 = px2double p1 --- Output: 2.0

---- ### Currency
data Currency = RUB | USD | EUR deriving (Show, Eq)
test11 = RUB == USD --- Output: False


---- ###2 Price_
data Price_ = Px_ Currency Double deriving (Show)
-- getters 
getPrice (Px_ _ d) = d
getCurr  (Px_ c _) = c
-- add
addPrice_ (Px_ cur1 p1) (Px_ cur2 p2) 
    | cur1 == cur2 = Px_ cur1 (p1+p2)
    | otherwise = undefined 
----test2
p21 = Px_ RUB 2.5
m21 = getPrice p21
c21 = getCurr p21
test21 = addPrice_ p21 p21 -- Output: Px_ RUB 5.0
--- p2 --- Output: Px_ RUB 2.5


---- ###3 Price'
data Price' = Px' {getCur'::Currency, getPx'::Double} deriving (Show)
instance Eq Price' where
  p1 == p2 = ( getCur' p1 == getCur' p2 ) && ( getPx' p1 == getPx' p2 )
addPrice' p1 p2 
    | getCur' p1 == getCur' p2 = Px' (getCur' p1) ( getPx' p1 + getPx' p2 )
    | otherwise = undefined 
----test3 
p31 = Px' RUB 2.5
--- p31 --- Output: Px' {getCur' = RUB, getPx' = 2.5} -- некрасиво!!
---- TODO31+ попробуем улучшить show в следующем типе Price
-- `+` после TODO означает что реализация получилась
m31 = getPx' p31
c31 = getCur' p31
test31 = addPrice' p31 p31 --- Output: Px' {getCur' = RUB, getPx' = 5.0}


---- ###4 Price
data Price = Px {getCur::Currency, getPx::Double} -- deriving (Show)
instance Eq Price where
  p1 == p2 = ( getCur p1 == getCur p2 ) && ( getPx p1 == getPx p2 ) 
instance Show Price where
  show p = show (getPx p) ++ " " ++ show (getCur p)
addPrice p1 p2 
    | getCur p1 == getCur p2 = Px (getCur p1) ( getPx p1 + getPx p2 )
    | otherwise = undefined
----test4
p41 = Px RUB 2.5
--- p41 --- Output: 2.5 RUB
test41 = addPrice p41 p41 -- Output: 5.0 RUB
p42 = Px USD 2.5
--- p42 --- Output: 2.5 USD
test42 = addPrice p41 p42 -- компилируется, но при запуске undefined
--- test42 --- Output: *** Exception: Prelude.undefined
---- ### заключение Price
-- (+) show с единицами измерения
-- (-) TODO41+ xотелось бы, чтобы Error была в compileTime
-- сделаем это в типе Price''


---- ###5 Price''
-- TODO41 частично реализовано в этом типе Price''
-- но show выводит ответ без указания вылюты
---- фантомные типы
{- Фантомным называется тип данных, в конструкторе типа которого содержится типовая переменная, отсутствующая в правой части объявления. Например, -}
-- newtype Price''' a = Price''' Double deriving (Show, Eq) 
-- :set -XGeneralizedNewtypeDeriving
newtype Price'' a = Px'' Double deriving (Num, Eq, Show)
-- newtype Price'' a = Px'' Double deriving (Eq, Show)
{- Фантомные типы позволяют на уровне типов хранить дополнительную информацию,
используемую при тайпчекинге, но не занимающую места в памяти во время исполнения. Величине Px'' 3 может 
быть приписано бесконечное множество разных фантомных типов, хотя во время исполнения это будет просто величина 
типа Double. -}
---- необитаемые или пустые типы данных
{- Haskell позволяет определять необитаемые или пустые типы данных, то есть такие
типы, которые не имеют ни одного значения. 
Это очень просто сделать, вот два таких типа,-}
data Rub
data Usd
-- Их смысл — в использовании вместо параметра a в конструкторе типа Px'':
p52 = Px'' 3 :: Price'' Rub
--- p52 --- Output: Price 3.0
--- :t p52 --- Output: p52 :: Price'' Rub
-- addPrice''
addPrice'' :: Price'' a -> Price'' a -> Price'' a
addPrice'' (Px'' d1) (Px'' d2) = Px'' (d1+d2)
----test5
p51 = Px'' 3
--- p51 --- Output: Price 3.0
--- :t p51 --- Output: p51 :: Price'' a
p53 = Px'' 3 :: Price'' Usd
--- :t p53 --- Output: p53 :: Price'' Usd
test51 = addPrice'' p51 p52 --- Output: Px'' 6.0
-- ошибка пропущена!!! `a` сложили с `Rub`
---- TODO.5.1 надо обеспечить обязательность задания типа `a`
test51' = p51 + p52*2 --- 3+3*2=9
test51'' = p51 + p52*p52 --- 3+3*3=12

test52 = addPrice'' p52 p52 --- Output: Px'' 6.0
-- отлично `Rub` сложили с `Rub`
test52' = p52 + p52*1 --- 3+3*1=6 
test52'' = p52*p52 --- 3*3=9 -- умножим `Rub` на `Rub` (так НЕЛЬЗЯ==НЕпонятнаРазмерность, но тут получилось) 
---- TODO.5.2 зря написали Num в deriving, т.к. для цен доступны только операции +,-,*(на число, но не на цену), т.е. класс Num слишком широк
--- test53 = addPrice'' p52 p53 --- compile Error (отлично!! ошибка в compileTime)
-- ошибка нельзя `Rub` + `Usd`
{- error:
    * Couldn't match type `Usd' with `Rub'
      Expected type: Price'' Rub
        Actual type: Price'' Usd
    * In the second argument of addPrice'', namely `p54'
-}
--- test53' = p52 + p53
-- compile-ошибка нельзя `Rub` + `Usd`
---- TODO52 надо как-то распечатать в какой валюте цена


---- ###6 Price'' + initPrice
initPrice cur px = Px'' px :: Price'' cur -- как передать сюда параметр cur ?!
p61 = initPrice RUB 3 
--- p61 --- Output: Px'' 3.0
--- :t p61 --- Output: p61 :: Price'' cur 
---- TODO61 как передать в Price'' параметр cur ?!
p62 = initPrice USD 3 
--- p62 --- Output: Px'' 3.0
--- :t p62 --- Output: p62 :: Price'' cur 


---- ###7 Price'' + usd2rub
usd2rub :: Price'' Usd -> Price'' Rub
usd2rub (Px'' p) = Px'' (p * crossCourse "Usd" "Rub" )
crossCourse "Usd" "Rub" = 70
crossCourse "Rub" "Usd" = 1/crossCourse "Usd" "Rub"
----test7
p62' = usd2rub p62
--- p62' --- Output: Px'' 210.0
--- :t p62' --- Output: p62' :: Price'' Rub 


---- ###8 Px
-- если у нас несколько (2-3-5) валют, то можно сделать так
-- определить несколько конструктора для типа Px
data Px = PxRub Double | PxUsd Double deriving (Eq,Show)
p81 = PxRub 2
p82 = PxUsd 3
-- определить функцию сложения для пар одинаковых конструкторов
addPx :: Px -> Px -> Px
addPx (PxRub d1) (PxRub d2) = PxRub (d1+d2)
addPx (PxUsd d1) (PxUsd d2) = PxUsd (d1+d2)
{-
*Main Data.Ratio> p81
PxRub 2.0
*Main Data.Ratio> addPx p81 p81
PxRub 4.0
*Main Data.Ratio> addPx p81 p82
*** Exception: Prices.hs:(163,1)-(164,43): Non-exhaustive patterns in function addPx
-}



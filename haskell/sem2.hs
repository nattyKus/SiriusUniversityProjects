module Demo where
import Data.Function

factorial n = if n == 0 then 1 else n * factorial (n - 1)

factorial' 0 = 1
factorial' n = n * factorial (n - 1)

doubleFact 0 = 1
doubleFact 1 = 1
doubleFact n = n * doubleFact (n - 2)

factorial'' 0 = 1
factorial'' n = if n < 0 then undefined else n * factorial' (n - 1)

factorial''' n | n < 0 = error "arg below 0"
               | n > 0 = n * factorial (n - 1)
               | n == 0 = 1

fibonacci 0 = 0
fibonacci 1 = 1
fibonacci n | n < 0 =  fibonacci (n + 2) - fibonacci (n + 1)
            | otherwise = fibonacci (n - 1) + fibonacci (n - 2)

factorial5 n | n >= 0 = helper 1 n
             | otherwise = error "arg below zero"
helper acc 0 = acc
helper acc n = helper (acc * n) (n-1)

fibonacci'acc n = fibonacci'helper 0 1 n

fibonacci'helper acc1 acc2 0 = acc1
fibonacci'helper acc1 acc2 1 = acc2
fibonacci'helper acc1 acc2 n | n > 0 = fibonacci'helper acc2 (acc1+acc2) (n-1)
                             | otherwise = fibonacci'helper (acc2-acc1) (acc1) (n+1)

iter' s v 0 = s
iter' s val n = iter' (s + val) val (n-1)
{- 
iter' 1e7 1e-7 1e7
1.000000100582838e7
-}

mono :: Char -> Char
mono = id

semiMono :: Char -> a -> Char
semiMono x y = x

{-
apply2 f x = f (f x)

apply2 (+5) 22
32

apply2 ("AB" ++) "CD"
"ABABCD"
-}

{-
flip f x y = f y x
-}

{-
on op f x y = f x `op` f y
-}

sumSquares x y = on (+) (^2) x y

-- функция должна перемножать вторые элементы пар переданных в неё
{-
multiSecond = op `on` f
multiSecond = on op f
multiSecond ('A',2)('E',7) = 14
-}

multiSecond = on op f
op = (*)
f = snd 

--лямбда функции
{-
let a = \x -> 2 * x + 7
let a x = 2 * x + 7

let f3 = \x y -> sqrt $ x^2 + y^2
let f3 = \x -> \y -> sqrt $ x^2 + y^2
let f3 x = \y -> sqrt $ x^2 + y^2
-}

-- суммировать первые элементы первых кортежей
p1 = ((1,2),(3,4))
p2 = ((3,4),(5,6))
sumFstFst' = (+) `on` (\pp-> fst $ fst pp)

{-
on3 :: (b -> b -> b -> c) -> (a -> b) -> a -> a -> a -> c
on3 op f x y z = undefined

-- Пример использования:
let sumSquares = (\x y z -> x + y + z) `on3` (^2)
sumSquares 1 2 3 = 14
-}

on3 op f x y z = op (f x) (f y) (f z)
sum3Squares = (\x y z -> x + y + z) `on3` (^2)

-- Напишите тело функции calc, в которой
-- возведите координаты векторов в квадрат 
-- и вычислите расстояние между получившимися векторами

vector1 = (1.0, 2.0)
vector2 = (3.0, 4.0)


sqr_coords (x, y) = (x^2, y^2)
dist p1 p2 = sqrt $ (fst p1 - fst p2)^2 + (snd p1 - snd p2)^2
dist' p1@(x1, y1) p2 = sqrt $ (x1 - fst p2)^2 + (snd p1 - snd p2)^2

calc_r x y = dist (sqr_coords x) (sqr_coords y)
-- a+b === (+) a b
-- max 3 4 == 3 `max` 4, mod 5 3 = 5 `mod` 3

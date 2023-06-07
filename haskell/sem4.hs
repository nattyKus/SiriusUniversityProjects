module Demo where

-- простая реализация корней
roots :: Double -> Double -> Double -> (Double, Double)
roots a b c = 
    (
        (-b - sqrt (b ^ 2 - 4 * a * c)) / (2 * a)
    ,
        (-b + sqrt (b ^ 2 - 4 * a * c)) / (2 * a)
    )
    
-- let с одним связыванием
roots' a b c = 
    let d = sqrt (b ^ 2 - 4 * a * c) in
    ((-b - d) / (2 * a), (-b + d) / (2 * a))

-- let со списком связываний
roots'' a b c = 
    let {d = sqrt (b ^ 2 - 4 * a * c); x1 = (-b - d) / (2 * a); x2 = (-b + d) / (2 * a)} in
    (x1, x2)

--- let с отступами
roots''' a b c = 
    let 
        d = sqrt (b ^ 2 - 4 * a * c)
        x1 = (-b - d) / (2 * a)
        x2 = (-b + d) / (2 * a)
    in (x1, x2)

factorial5 n | n >= 0 = helper 1 n
             | otherwise = error "arg below zero"
helper acc 0 = acc
helper acc n = helper (acc * n) (n - 1)


factorial6 n
    | n >= 0 = let
        helper acc 0 = acc
        helper acc n = helper (acc * n) (n - 1)
      in helper 1 n
    | otherwise = error "arg below zero"

{-
Задание: Реализуйте функцию seqA, находящую элементы 
следующей рекуррентной последовательности

map seqA [0..20]
[1,2,3,3,2,-1,-5,-10,-13,-13,-6,7,27,46,59,51,18,-49,-133,-218,-253]
a0=1;a1=2;a2=3;a(k+3)=a(k+2)+a(k+1)−2a(k)

проверка:
seqA 301
1276538859311178639666612897162414

-}

seqA :: Integer -> Integer
seqA 0 = 1
seqA 1 = 2
seqA 2 = 3
seqA n = let 
    helper_secA _ _ s3 0 = s3
    helper_secA s1 s2 s3 n = helper_secA s2 s3 (s3 + s2 - 2*s1) (n-1)
    in helper_secA 1 2 3 (n-3)
-- seqA n = seqA (n-1) + seqA (n-2) - 2 * seqA (n-3)

{-
Задание: Реализуйте функцию, находящую сумму и 
количество цифр десятичной записи заданного целого числа.

проверка:
sum'n'count (-39)
(12,2)

-}

sum'n'count :: Integer -> (Integer, Integer)
sum'n'count x = let
    helper'counter 0 s n = (s, n)
    helper'counter x s n = helper'counter ((abs x) `div` 10) (s + ((abs x) `mod` 10)) (n+1)
    in helper'counter x 0 0
    
sum'n'count' :: Integer -> (Integer, Integer)
sum'n'count' x = let
    sum2 0 s = s
    sum2 x s = sum2 ((abs x) `div` 10) (s + ((abs x) `mod` 10))
    cnt 0 n = n
    cnt x n = cnt ((abs x) `div` 10) (n+1)
    in (sum2 x 0, cnt x 0)

{-
Задание: Реализуйте функцию, находящую значение 
определённого интеграла от заданной функции f на 
заданном интервале [a,b] методом трапеций. 
(Используйте равномерную сетку; достаточно 1000 
элементарных отрезков.)

-- проверка:
integration sin 0 pi
-2.0
-}
integration :: (Double -> Double) -> Double -> Double -> Double
integration f a b = let
    helper'square b step s | b-step <= 0 = s + ((abs (f 0)) + (abs (f b)))*step/2
                           | otherwise = helper'square (b-step) step (s + ((abs (f (b-step))) + (abs (f b)))*step/2)
    in helper'square (b-a) ((b-a) / 1000000) 0

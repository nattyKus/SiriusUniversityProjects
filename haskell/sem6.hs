module Demo where

import Prelude -- hiding (filter,takeWhile,dropWhile,span,break)
import Data.Char

{-
filter :: (a -> Bool) -> [a] -> [a]
filter p [] = []
filter p (x:xs)
  | p x = x : filter p xs
  | otherwise = filter p xs


takeWhile :: (a -> Bool) -> [a] -> [a]
takeWhile _ [] =  []
takeWhile p (x:xs)
            | p x =  x : takeWhile p xs
            | otherwise =  []


dropWhile :: (a -> Bool) -> [a] -> [a]
dropWhile _ [] =  []
dropWhile p xs@(x:xs')
            | p x =  dropWhile p xs'
            | otherwise =  xs


-- 'span' @p xs@ is equivalent to @('takeWhile' p xs, 'dropWhile' p xs)@
span x = (takeWhile x, dropWhile x)
span :: (a -> Bool) -> [a] -> ([a],[a])
span _ xs@[] =  (xs, xs)
span p xs@(x:xs')
         | p x =  let (ys,zs) = span p xs' in (x:ys,zs)
         | otherwise =  ([],xs)

-- 'break' @p@ is equivalent to @'span' ('not' . p)@.
break :: (a -> Bool) -> [a] -> ([a],[a])
#if defined(USE_REPORT_PRELUDE)
break p =  span (not . p)
#else
-- HBC version (stolen)
break _ xs@[] =  (xs, xs)
break p xs@(x:xs')
           | p x =  ([],xs)
           | otherwise  =  let (ys,zs) = break p xs' in (x:ys,zs)
-}          
           
{-
Напишите функцию readDigits, принимающую строку 
и возвращающую пару строк.
Первый элемент пары содержит цифровой префикс 
исходной строки, а второй - ее оставшуюся часть.

GHCi> readDigits "365ads"
("365","ads")
GHCi> readDigits "365"
("365","")

-}

-- В решении вам поможет функция isDigit из модуля Data.Char.

readDigits::String -> (String,String)
readDigits = span isDigit

{-
Реализуйте функцию filterDisj, принимающую 
два унарных предиката и список, и возвращающую 
список элементов, удовлетворяющих хотя бы одному из предикатов.
--проверка:
GHCi> filterDisj (< 10) odd [7,8,10,11,12]
[7,8,11]
-}

filterDisj :: (a -> Bool) -> (a -> Bool) -> [a] -> [a]
filterDisj u1 u2 l = filter (helper_filterDisj u1 u2) l
helper_filterDisj u1 u2 l = (u1 l) || (u2 l)
--  helper_filterDisj u1 u2 = \l -> (u1 l) || (u2 l)
-- filterDisj u1 u2 l = filter (\l -> (u1 l) || (u2 l)) l


--- ещё одна задача на закрепление функций высших порядков
{-
Напишите реализацию функции qsort. 
Функция qsort должная принимать на вход список 
элементов и сортировать его в порядке возрастания 
с помощью сортировки Хоара: для какого-то 
элемента x изначального списка (обычно выбирают первый) 
делить список на элементы меньше и не меньше x, 
и потом запускаться рекурсивно на обеих частях.
подробней про Хоара: 
https://ru.wikipedia.org/wiki/Быстрая_сортировка 

GHCi> qsort [1,3,2,5]
[1,2,3,5]

Разрешается использовать только функции, доступные из библиотеки Prelude.
-}

qsort [] = []
qsort [a] = [a]
qsort (x:xs) = qsort (filter (<x) xs) ++ [x] ++ qsort (filter (>=x) xs)

{-
применение функции к элементам списка с образованием списка из результатов
map (const 42) "ABC" -> [42,42,42] 

map :: (a -> b) -> [a] -> [b]
map _ [] = []
map f (x:xs) = f x : map f xs

сцепление списка списков
concat [[1,2],[3,4]] -> [1,2,3,4]

concat :: [[a]] -> [a]
concat [] = []
concat (xs:xss) = xs ++ concat xss 

f возвращает список, map возвращает список списков, потом сцепляем в общий список
concatMap (\x -> [x,x]) "ABC" -> "AABBCC" 

concatMap :: (a -> [b]) -> [a] -> [b]
concatMap f = concat . map f
-}

{-
Напишите функцию squares'n'cubes, принимающую список чисел,
--и возвращающую список квадратов и кубов элементов исходного списка.

GHCi> squares'n'cubes [3,4,5]
[9,27,16,64,25,125]

-}
squares'n'cubes :: Num a => [a] -> [a]
squares'n'cubes = concatMap (\x -> [x^2, x^3])
--concat [map (\x -> x^2) x, map (\x -> x^3) x]


{- Напишите функцию insertElem, которая 
принимает на вход два аргумента: элемент и список.
И возвращает все возможные варианты как этот элемент 
может быть добавлен в список, то есть добавить элемент 
на все возможные позиции списка.

примеры:
*Demo> insertElem 'z' "ABCDEF"
["zABCDEF","AzBCDEF","ABzCDEF","ABCzDEF","ABCDzEF","ABCDEzF","ABCDEFz"]
*Demo> insertElem 0 [1,2,3]
[[0,1,2,3],[1,0,2,3],[1,2,0,3],[1,2,3,0]]
-}

insertElem :: t -> [t] -> [[t]]
insertElem x [] = [[x]]
insertElem x (y:ys) = (x:y:ys) : map (y:) (insertElem x ys)

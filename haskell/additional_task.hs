module Demo where
import Prelude hiding (reverse)

{-
Доп задание для пропустивших 11.02:

Реализуйте функцию принимающую три аргумента: reverse lst a b 
которая разворачивает часть списка задом наперед, начиная с элемента a и заканчивая b.
нумерация a и b начинается с ноля, номера элементов указаны включительно.

Нельзя использовать функции стандартной библиотеки 
take, head, reverse, split, splitAt и им подобные.
Операторы использовать можно (в частности ++)

--Например:
reverse [1,2,3,4,5,6,7,8,9,10] 2 6
[1,2,7,6,5,4,3,8,9,10]

--Функция должна работать и на бесконечном списке. 
reverse [1..] 2 6
-}

reverse lst a b = let
    helper_reverse a b lst@(l:ls) | a > 0 = l : helper_reverse (a-1) (b-1) ls
                                  | b >= 0 = lst!!b : helper_reverse (a-1) (b-1) lst
                                  | a < 0 = helper_reverse (a+1) b ls
                                  | otherwise = lst
    in helper_reverse a b lst

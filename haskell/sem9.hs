module Demo where
import Prelude hiding (foldr, foldl, sum,prod,or,and,cycle,
    unzip, unzip3)

foldr :: (a -> b -> b) -> b -> [a] -> b
foldr f ini []     = ini
foldr f ini (x:xs) = x `f` foldr f ini xs

{-
cycle                   :: [a] -> [a]
cycle []                = error "cycle"
cycle xs                = xs' where xs' = xs ++ xs'
-}

--Определите с помощью свёртки следующие функции:
sum, prod  :: Num a => [a] -> a
or,  and   :: [Bool] -> Bool
cycle      :: [a] -> [a]

unzip      :: [(a,b)] -> ([a],[b])
unzip3     :: [(a,b,c)] -> ([a],[b],[c])

sum = foldr (+) 0
prod = foldr (*) 1
or = foldr (||) False
and = foldr (&&) True
cycle l = foldr (\x s -> x ++ s) [] [l,(cycle l)]
cycle' l = foldr (\x s -> x ++ (cycle' l)) [] [l]
unzip = foldr (\(x1,x2) (s1,s2) -> (x1:s1,x2:s2) ) ([],[])
unzip3 = foldr (\(x1,x2,x3) (s1,s2,s3) -> (x1:s1,x2:s2,x3:s3) ) ([],[],[])

foldl :: (b -> a -> b) -> b -> [a] -> b
foldl f ini []     = ini
foldl f ini (x:xs) = foldl f (f ini x) xs

{-Реализуйте функцию meanList, которая находит среднее значение элементов списка, 
используя однократный вызов функции свертки. Не использовать функцию length.

GHCi> meanList [1,2,3,4]
2.5
Постобработка считается допустимой, то есть предполагаемая 
реализация функции meanList имеет вид
meanList = someFun . foldr someFoldingFun someIni
-}

--Заготовка:
meanList :: [Double] -> Double
meanList = (\(x, y) -> x / y) . foldr (\x (s,p) -> (x+s, p+1)) (0.0, 0.0)
module Demo where
import Prelude
import Data.Char ( isLower )

{- Реализуйте функцию delAllUpper, удаляющую из текста все слова, целиком состоящие 
из символов в верхнем регистре. Предполагается, что текст состоит только из 
символов алфавита и пробелов, знаки пунктуации, цифры и т.п. отсутствуют. -}

dellAllUpper::String -> String
dellAllUpper = unwords . filter (any isLower). words

max3 :: Ord a => [a] -> [a] -> [a] -> [a]
max3 = zipWith3 (\x y z -> max x (max y z))

nats n = n : nats (n+1)
squares = map (^2) $ nats 1

{- задача: с помощью zipWith реализовать бесконечный список последовательнсоит Фиббоначи 
-- проверка:
take 10 $ fibStream
[0,1,1,2,3,5,8,13,21,34]-}

fibStream = 0:1: zipWith (+) fibStream (tail fibStream)
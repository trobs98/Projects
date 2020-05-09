--
-- Assignment : 4
-- Author     : Tyler Roberts
-- Email      : trober64@uwo.ca
--
-- sorts a list of integers using Insertion Sort
-- 

-- Function Declarations
insert :: Int -> [Int] -> [Int] 
isort :: [Int] -> [Int]

-- Inserts an integer into a sorted list of integers
insert y [] = [y]
insert y (x:xs)
 | y <= x = y : x : xs
 | otherwise = x : insert y xs

--Insertion Sort Function that sorts an unsorted list of integers
isort [] = []
isort (x:xs) = insert x (isort xs)  


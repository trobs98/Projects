--
-- Assignment : 4
-- Author     : Tyler Roberts
-- Email      : trober64@uwo.ca
--
-- Function that mergesorts a list of numbers
--

-- Function Declaration
merge :: [Int] -> [Int] -> [Int]
msort :: [Int] -> [Int]

-- in case input number arrays are empty 
merge [] [] = []
merge [] x = x
merge x [] = x

-- regular merge function
merge (x:xs) (y:ys)
 | x <= y = x : merge xs (y:ys)
 | otherwise = y : merge (x:xs) ys 

-- Merge Sort function
msort [] = []
msort x 
 | length x == 1 = x
 | otherwise = merge (msort firsthalf) (msort secondhalf)   
 where half = length x `div` 2
       firsthalf = take half x
       secondhalf = drop half x  

--
-- Assignment : 4
-- Author     : Tyler Roberts
-- Email      : trober64@uwo.ca
-- 
-- Contains a function that allows you to compute the result of a^n
--

-- Function Declaration
pow :: Integer -> Integer -> Integer

pow a n
 | n > 0 = a * pow (a) (n-1)
 | otherwise = 1 
 

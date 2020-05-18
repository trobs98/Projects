--
-- Assignment : 4
-- Author     : Tyler Roberts
-- Email      : trober64@uwo.ca
--
-- function to calculte a^n using pattern matching
--

-- Function Declaration
pow' :: Integer -> Integer -> Integer

pow' _ 0 = 1
pow' a n = a* pow' (a) (n-1)
 


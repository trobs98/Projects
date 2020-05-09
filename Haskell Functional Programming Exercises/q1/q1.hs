--
-- Assignment : 4
-- Author     : Tyler Roberts
-- Email      : trober64@uwo.ca
--
-- Creating a function to multiply two numbers using only the "+" operator
--

-- Function Declaration
mult :: Int -> Int -> Int

mult a b
 | b > 0 = a + mult (a) (b-1)
 | otherwise = 0;

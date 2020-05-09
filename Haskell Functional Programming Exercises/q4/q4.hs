--
-- Assignment : 4
-- Author     : Tyler Roberts
-- Email      : trober64@uwo.ca
--
-- Several Functions to help understand list comprehensions 
--

-- List of odd numbers from 0-10
odds = [1,3..10]

-- Infinite list of even numbers
positiveEvens = [2,4..]

--Infinite list of number of 2^x
powersOfTwo = [2^x | x <- [0,1..]]

-- Function to determine if the number is prime
isPrime x
 | x <= 1 = False
 | otherwise = null [k | k <- [2..x-1], x `mod` k==0]

-- Infinite list of prime numbers
primeNumbers = [ x | x <- [1,2..], isPrime x]

-- Function to get first N prime numbers
firstNPrimes n = take n primeNumbers
 

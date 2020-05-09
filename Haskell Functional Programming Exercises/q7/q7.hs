--
-- Assignment : 4
-- Author     : Tyler Roberts
-- Email      : trober64@uwo.ca
--
-- Manipulates an input string and outputs the result using l33t function
--

import Data.Char (ord, chr)

--All function declarations 
isConst :: Int -> Bool
isUpper :: Int -> Bool
isE :: Int -> Bool
isI :: Int -> Bool
isOtherVowel :: Int -> Bool
isExMark :: Int -> Bool
l33t :: String -> String

--Helper functtions

-- Checks if x is a constant
isConst x
 | x >= 98 && x <=100 || x >=102 && x <=104 || x >=106 && x<=110 || x>=112 && x<=116 || x>=118 && x<=122 || x >= 66 && x <=68 || x >=70 && x <=72 || x >=74 && x<=78 || x>=80 && x<=84 || x>=86 && x<=90 = True
 | otherwise = False

-- Checks if x is uppercase
isUpper x
 | x >=65 && x <= 90 = True
 | otherwise = False

-- Checks if x is e or E
isE x
 | x == 69 || x == 101 = True
 | otherwise = False

-- Checks if x is i or I
isI x
 | x == 73 || x == 105 = True
 | otherwise = False

-- Checks if x is any of the other vowels
isOtherVowel x
 | x == 65 || x == 97 || x == 79 || x == 111 || x == 85 || x == 117 = True
 | otherwise = False

--Checks if x is an exclamation mark
isExMark x
 | x == 33 = True
 | otherwise = False

l33t [] = []
l33t (x:xs)
 | isConst (ord x) == True && isUpper (ord x) == True = x : l33t (xs)
 | isConst (ord x) == True && isUpper (ord x) == False = chr((ord x) - 32) : l33t (xs)     
 | isE (ord x) == True = '3' : l33t(xs)
 | isI (ord x) == True = '1' : l33t(xs)
 | isOtherVowel (ord x) == True && isUpper (ord x) == True = chr((ord x) + 32) : l33t (xs) 
 | isOtherVowel (ord x) == True && isUpper (ord x) == False = x : l33t (xs)
 | isExMark (ord x) == True = '!' : '!' : '!' : '1' : '1' : '1' : 'o' : 'n' : 'e' : 'o' : 'n' : 'e' : l33t (xs)
 | otherwise = x : l33t (xs)


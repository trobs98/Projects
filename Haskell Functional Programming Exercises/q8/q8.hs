-- 
-- Assignment : 4 
-- Author : Tyler Roberts 
-- Email : trober64@uwo.ca 
-- 
-- Converts a hexadecimal string to a decimal integer 
--

hexToDec :: Char -> Int
hexStrToDec :: String -> Int

--Function to convert the string character to an integer
hexToDec x
 | x == '0' = 0
 | x == '1' = 1
 | x == '2' = 2
 | x == '3' = 3
 | x == '4' = 4
 | x == '5' = 5
 | x == '6' = 6
 | x == '7' = 7
 | x == '8' = 8
 | x == '9' = 9
 | x == 'A' || x == 'a' = 10
 | x == 'B' || x == 'b' = 11
 | x == 'C' || x == 'c' = 12
 | x == 'D' || x == 'd' = 13
 | x == 'E' || x == 'e' = 14
 | x == 'F' || x == 'f' = 15
 | otherwise = 16


--For when there is the 0x or 0X prefix
hexStrToDec ('0' : 'x' : xs) = hexStrToDec (xs)
hexStrToDec ('0' : 'X' : xs) = hexStrToDec (xs)

hexStrToDec x
 | length x /= 0 && hexToDec(last(x)) /= 16 = (hexToDec(last(x)))+(16*(hexStrToDec(init(x))))
 | length x /= 0 && hexToDec(last(x)) == 16 = error "Non-hexadecimal digits present."
 | otherwise = 0

# Code from https://stackoverflow.com/questions/4502429/recursive-factorial-function
# For testing purposes only

def factorial( n ):
   if n <1:   # base case
       return 1
   else:
       returnNumber = n * factorial( n - 1 )  # recursive call
       return returnNumber

print factorial(7)

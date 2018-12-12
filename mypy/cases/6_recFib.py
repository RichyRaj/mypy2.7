# Code from: https://realpython.com/python-thinking-recursively
# Only for testing purposes

def fibonacci_recursive(n):
    # Base case
    if n == 0:
        return 0
    if n == 1:
        return 1
    # Recursive case
    else:
        return fibonacci_recursive(n-1) + fibonacci_recursive(n-2)


print fibonacci_recursive(15)

y = 10000

def news(a, b):
    return a + b + two(a, b);

def two(x, y):
    return x + y

print two(1, 2) # 3
print two() # Err
print two(1) # Err
print two(1, 2, 99) # Err
print two(100, ((200 - 100) * (99-100))) # 0
print two("100", "Hello") # 100Hello

print news(2, 100) # 204
print news(2, 1) # 6
print news(2) # Err

x = 5

def fact():
    if x == 0:
        return 1
    x -= 1
    return (x + 1) * fact()

print fact()

def twice(n):
    if n < 0:
        return -2
    if n == 0:
        return 2
    else:
        return 2 * n

minus = -1

def changeSign(a):
    return a * -1

print twice()
print twice(2)
print twice(0)
print twice(-100)
print twice(200)


print changeSign()
print changeSign(100)
print changeSign(twice(100))
print changeSign(twice(0))
print changeSign(twice(-100))

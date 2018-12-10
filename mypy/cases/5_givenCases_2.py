def f():
    return 7*2
def g():
    print 15
    x = 12
    def h():
        return x
    print h()
    return 2 * x

print f()
print g()

# 14
# 15
# 12
# 24

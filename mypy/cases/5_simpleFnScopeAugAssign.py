x = 8
def test():
    x = 100
    print "Inner 1"
    print x

def test2():
    x += 10
    print "Inner 2"
    print x
    x -= 10
    print "Inner 2"
    print x
    x *= 10
    print "Inner 2"
    print x
    x /= 10
    print "Inner 2"
    print x
    x //= 10
    print "Inner 2"
    print x
    x %= 10
    print "Inner 2"
    print x
    x **= 10
    print "Inner 2"
    print x

test()
test2()

print "Global"
print x

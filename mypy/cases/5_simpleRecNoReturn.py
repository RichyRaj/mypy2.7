n = 14

def test():
    if n > 0:
        print "Hello"
        n = n -1
        test()
test()

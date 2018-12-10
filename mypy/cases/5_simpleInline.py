def test(): print 2

a = 2

def test2(): return 21 + a

def test3(): return 90 + test2()

def test4(): return ((7 + test3()) == 120)

test()
print test2()
print test3()
print test4()


if test4() == 1.0: print "Indeed"

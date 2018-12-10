def outer():
    print "Outer"
    a = 200
    print a
    def inner():
        print "Inner"
        b = 100
        return a + b
        print "After return inner"
        print "After return inner"
    print "From Outer"
    print inner()
    print "From Outer + Inner"
    return 500 + inner()
    print "After return outer"
    return

print outer()

a = 2

def x():
    print "Outer 1"
    b = 100
    a = 10
    print a * b
    def y():
        print "Inner 1"
        print a + b
        a = 98
        print a
    y()
    print "Outer 1"
    print a

x()
print "Global"
print a

def y():
    print "Outer 2"
    print a

y()

# Outer 1
# 1000
# Inner 1
# 110
# 98
# Outer 1
# 10
# Global
# 2
# Outer 2
# 2


# STR: Outer 1
# INT: 1000
# STR: Inner 1
# INT: 110
# INT: 98
# STR: Outer 1
# INT: 10
# STR: Global
# INT: 2
# Outer 2
# 2

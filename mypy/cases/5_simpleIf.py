# print "====== Equals========"
print 2==2 # 1
print 22==2 # 0
# print "========================="

# print "====== Not Equals========"
print 12 != 12 # 0
print 12 != 1 # 1
a = 100
b = 20
print a != b # 1
# print "========================="

# print "====== Greater ========"
print 12 > 12 # 0
print 12 > 10 # 1
print 12 > 42 # 0
# print "========================="

# print "====== Greater EQ ========"
print 12 >= 12 # 1
print 12 >= 10 # 1
print 12 >= 42 # 0
# print "========================="

# print "====== Lesser ========"
print 12 < 12 # 0
print 12 < 10 # 0
print 12 < 42 # 1
# print "========================="

# print "====== Lesser EQ ========"
print 12 <= 12 # 1
print 12 <= 10 # 0
print 12 <= 42 # 1
# print "========================="

x = 2

if 8 == 8:
    print "hello"
    print "new"
    def test():
        print x
        x = 9
        print x
    test()
    print "end"
    print x


if 10 != 2:
    print "NQ"

if 10 > 12:
    print "False"

if 10 < 12:
    print "Yes"

x = 12
y = 12
if x >= y:
    print "Yes 2"

if 99 <= x:
    print "No"

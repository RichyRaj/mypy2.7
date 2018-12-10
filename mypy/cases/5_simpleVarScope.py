a = 5
print "At Global Level :"
print a
def fn():
    a = 7
    print "At Local Level :"
    print a
    a = 9
    print "At Local Level :"
    print a
fn()
print "At Global Level :"
print a

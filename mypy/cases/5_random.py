def f():
    print "First"

def f():
    print "Second"

f()
f()

def i():
    print "Outer i"

def o():
    def i():
        print "inner i"
    i()

o()
i()

if 1:
    print "hello"


x = 99

def f():
  x = x + 7
  print x
  def g():
    print x
  g()



f()
print x

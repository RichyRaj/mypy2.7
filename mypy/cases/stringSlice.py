a = "Hello World!"
b = "string"
c = "Carrick16"
# ================ Indexing test cases - Start =============================
print a[2]
print a[99.8]
print a[100]
print a["sad"]
f = a[-2]
print f
# Why not ?
g = a[10 - 10 * 2 + (1 + (6 / 2))]
print g
# ================ Indexing test cases - End =============================

# ================ Slicing test cases - Start =============================
print b[:]
print b[2:]
print a[:8]
print a[-2:]
print a[4:10]
print b[:-1]
# b[-1:0] # TEST OK ! RETURNS AN EMPTY STRING. CODE EDITORS HANDLE THEM WIERDLY.
print b[:] + 'ify'
print b[2:]
print b[2:100]
start = -1
end = 4
print b[start:]
# b[start:end] # TEST OK ! RETURNS AN EMPTY STRING. CODE EDITORS HANDLE THEM WIERDLY.
print b[end-1:start]
print a[-7:-3]
# a[-7:-6] # TEST OK ! RETURNS AN SPACE. CODE EDITORS HANDLE THEM WIERDLY.
c = c[:-2]
print c
# b[100:] # TEST OK ! RETURNS AN SPACE. CODE EDITORS HANDLE THEM WIERDLY.
print b[-100:]
# b[2:-99] TEST OK ! RETURNS AN SPACE. CODE EDITORS HANDLE THEM WIERDLY.
print b[2:-3]
# b[-1:4] TEST OK ! RETURNS AN SPACE. CODE EDITORS HANDLE THEM WIERDLY.
# # ================ Slicing test cases - End =============================

import math
u = [0, 1023]
arr = []
SZ = 60
for i in range(1, SZ):
    o = math.gcd(i, SZ-i)
    arr.append(list(u))
    u[1] -= i // o
    u[0] += (SZ-i) // o

for i in range(1, SZ):
    o = math.gcd(i, SZ-i)
    arr.append(list(u))
    u[1] -= (SZ-i) // o
    u[0] -= i // o

for i in range(1, SZ):
    o = math.gcd(i, SZ-i)
    arr.append(list(u))
    u[1] += i // o
    u[0] -= (SZ-i) // o

for i in range(1, SZ):
    o = math.gcd(i, SZ-i)
    arr.append(list(u))
    u[1] += (SZ-i) // o
    u[0] += i // o

print(len(arr))
for i, j in arr[::-1]:
    print(i, j)
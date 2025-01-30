import math

o = - math.log10(5)
u = math.log10((math.sqrt(5) + 1)/2)
#u2 = math.log10((1 - math.sqrt(5))/2)
a, b = 1, 1

for i in range(500):
    t = u*(i-2)+o
    print(int(math.pow(10, t - int(t) + 50)))
    print(a)
    a, b = b, a+b

print(u)
print(o)
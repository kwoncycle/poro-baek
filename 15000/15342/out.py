import random

l = random.choices(list(range(5000)), k=200)

print(100, 100, 0)
for i in range(199):
    print(l[i], 2*l[i])
print(0, 1)
print(0, 0, 0)
import random

print(500, 500)

for i in range(500):
    for j in range(500):
        print(random.randint(1, 100000), end = ' ')
    print()

print(50000)
for i in range(50000):
    print(i%400+1, 1, 50, 1, 400, 3)
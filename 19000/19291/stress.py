from random import randint
import subprocess
from tqdm import tqdm
for cnt in tqdm(range(10000)):
    n = randint(1, 5)
    l = randint(1, 20)
    r = randint(l, 20)
    points = []
    for i in range(n):
        x = randint(-10, 10)
        y = randint(-10, 10)
        s = randint(-100, 100)
        points.append([x,y,s])

    f = open('input', 'w')
    f.write(str(n) + " " + str(l) + " " + str(r) + "\n")
    for x,y,s in points:
        f.write(str(x) + " " + str(y) + " " + str(s) + "\n")

    ansmax = 0
    for xi in range(-100, 100):
        for yi in range(-100, 100):
            ans = 0
            for x,y,s in points:
                d = max(abs(x-xi), abs(y-yi))
                if l <= d and d <= r:
                    ans += s
            ansmax = max(ans, ansmax)

    f.close()
    subprocess.call("./solve < input > output1", shell=True)

    f = open('output1', 'r')
    a = int(f.readline())
    if a != ansmax:
        print(ansmax)
        print(n, l, r)
        for x,y,s in points:
            print(x, y, s)
        exit(0)
    f.close()
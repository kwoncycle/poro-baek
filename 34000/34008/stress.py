from subprocess import *
from tqdm import tqdm
from random import *

for _ in tqdm(range(100000)):
    n = randint(3, 5)
    f = open("input", "w")
    
    arr1 = [randint(1, 2) for _ in range(n)]
    arr2 = [randint(1, 2) for _ in range(n)]
    k = randint(1, 7)
    U1 = [randint(1, 50) for _ in range(n)]
    U2 = [randint(1, 50) for _ in range(n)]
    f.write(str(n) + " " + str(k) + "\n")
    for i in arr1:
        f.write(str(i) + " ")
    f.write("\n")
    for i in arr2:
        f.write(str(i) + " ")
    f.write("\n")
    for i in U1:
        f.write(str(i) + " ")
    f.write("\n")
    f.write("0 "*(n+1) + "\n")
    for i in U2:
        f.write(str(i) + " ")
    f.write("\n")
    f.close()
    ans = 0
    for i in range(3**n):
        i1 = i
        score = 0
        ttl = 0
        for j in range(n):
            if i1%3 == 1:
                score += arr1[j]
                ttl += U1[j]
            elif i1%3 == 2:
                score += arr2[j]
                ttl += U2[j]
            i1 //= 3
        if score <= k-1:
            ans = max(ans, ttl)
    U = run(["./solve < input"], shell=True, capture_output=True)
    U = int((U.stdout).rstrip())
    if U != ans:
        print(U)
        print(ans)
        exit(0)

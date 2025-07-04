from tqdm import tqdm
from random import randint
from subprocess import *
n = 7
for _ in tqdm(range(100000)):
    i = randint(0, 63)
    arr1 = []
    arr2 = []
    for j in range(6):
        if (i >> j) & 1:
            arr1.append(j+1)
        else:
            arr2.append(j+1)
    arr1.append(7)
    for j in arr2[::-1]:
        arr1.append(j)
        
    for i in range(128):
        f = open('input', 'w')
        f.write(str(n) + "\n")
        t = ""
        for j in range(7):
            if (i >> j) & 1:
                t = t + str(arr1[j]) + " "
            else:
                t = t + "0 "
        f.write(t)
        f.close()
        G = run(["./solve < input"], shell=True, capture_output=True)
        o = G.stdout
        if o[0] == ord('*'):
            print(t)
            print(o)
            exit(0)
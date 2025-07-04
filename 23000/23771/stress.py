from subprocess import *
from tqdm import tqdm
from random import randint, shuffle

for _ in tqdm(range(10000)):
    n = randint(3, 5)
    arr = [randint(1, 5) for _ in range(n)]    
    f = open("input", "w")
    f.write(str(n) + "\n")
    for i in arr:
        f.write(str(i) + " ")
    f.write("\n")
    shuffle(arr)
    for i in arr:
        f.write(str(i) + " ")
    f.write("\n")
    f.close()

    U = run(["./solve < input"], shell=True, capture_output=True)
    if U.stdout[0] == ord('s'):
        break
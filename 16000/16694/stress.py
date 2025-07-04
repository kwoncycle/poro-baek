from tqdm import tqdm
from random import randint, choice
from subprocess import run

S = list("ab")

for _ in tqdm(range(10000)):
    n = randint(1, 4)
    m = randint(2, 10)
    U = "".join(choice(S) for _ in range(m))
    inp = ""
    inp = inp + str(n) + "\n"
    inp = inp + U + "\n"
    for i in range(n):
        o = randint(1, m)
        inp = inp + "".join(choice(S) for _ in range(o)) + "\n"
    
    U1 = run(["./solve"], input=inp, shell=True, capture_output=True, text=True).stdout
    U2 = run(["./molamola/solve"], input=inp, shell=True, capture_output=True, text=True).stdout

    if U1 != U2:
        print(inp)
        break
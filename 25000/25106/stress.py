from subprocess import *
from random import randint
from tqdm import tqdm

for _ in tqdm(range(1000)):
    f = open('input', 'w')
    n = randint(1, 20)
    m = randint(1, 20)
    k = randint(1, 10)

    st = set()
    while len(st) < k:
        st.add((randint(1, n), randint(1, m)))
    st = list(st)
    assert len(st) == k
    q = 10
    f.write(str(n) + " " + str(m) + "\n" + str(k) + "\n")
    for i in range(k):
        x, y = st[i]
        val = randint(-10, 10)
        f.write(str(x) + " " + str(y) + " " + str(val) + "\n")
    f.write(str(q) + "\n")
    for i in range(q):
        h = randint(1, n)
        x = randint(1, m)
        y = randint(y, m)
        f.write(str(h) + " " + str(x) + " " + str(y) + "\n")

    f.close()

    res1 = run(["./solve < ./input"], capture_output=True, text=True, shell=True)
    res2 = run(['./solve1 < ./input'], capture_output=True, text=True, shell=True)

    if res1.stdout != res2.stdout:
        print(res1.stdout)
        print(res2.stdout)
        assert False


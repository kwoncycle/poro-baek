from tqdm import tqdm
import random

n = int(input())

r = [i for i in range(2*n)]
sm = 0.0
for _ in tqdm(range(10000000)):
    x = list(random.sample(r, n))
    
    y = [1 for _ in range(2*n)]
    for i in x:
        y[i] = 0
    y1 = []
    for i in range(2*n):
        if y[i]:
            y1.append(i)
    q = n-1
    cnt = 0
    x.sort()
    for i in range(n-1, -1, -1):
        if y1[q] > x[i]:
            cnt += i+1
            q -= 1
    if _ < 20:
        print(x, y1, cnt)
    sm += float(cnt)/10000000.0

print(sm)
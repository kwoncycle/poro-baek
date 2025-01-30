pl = []
nm = [1 for _ in range(10001)]

for i in range(2,10001):
    if nm[i]:
        for j in range(2*i, 10001, i):
            nm[j] = 0
        pl.append(i)

x = len(pl)
DP = [[1 for __ in range(10001)] for _ in range(x+1)]
for i in range(1, x+1):
    p = pl[i - 1]
    for j in range(1, 10001):
        DP[i][j] = DP[i-1][j]
        pp = p
        while j >= pp:
            DP[i][j] = max(DP[i][j], DP[i-1][j-pp] * pp)
            pp *= p

t = int(input())
for _ in range(t):
    n = int(input())
    o = DP[x][n]
    DRK = []
    for p in pl:
        g = 1
        while o % p == 0:
            o //= p
            g *= p
        if g > 1:
            DRK.append(g)
    DRK.sort()
    s = sum(DRK)
    for i in range(1, n-s+1):
        print(i, end = ' ')
    index = n-s+1
    for r in DRK:
        for j in range(r):
            print(index + (j+1)%r, end = ' ')
        index += r
    print()
#from tqdm import tqdm
C = [[0 for _ in range(1004+1)] for i in range(1004)]
#D = [[0 for _ in range(1004+1)] for i in range(1004)]
for i in range(1, 1002):
    C[i][i] = 1
    C[i][0] = 1
    #D[i][i] = 0
    #D[i][0] = 0

for i in (range(1, 1002)):
    for j in range(1, i):
        C[i][j] = C[i-1][j-1] + C[i-1][j]
        #D[i][j] = len(bin(C[i][j])) - 3
C[0][0] = 1
#D[0][0] = 0
n, d, r = map(int, input().split())

DP = [[[0 for i in range(n+1)] for j in range(d+1)] for k in range(n+1)]

for j in range(d+1):
    for k in range(r+1):
        if r - j > k:
            continue
        if j != 0 and r-1 < k:
            continue
        DP[r][j][k] = j + r

for i in (range(r+1, n+1)):
    for j in range(d+1):
        for k in range(i+1):
            if i - j > k:
                continue
            if j != 0 and i-1 < k:
                continue
            if k > 0:
                if i - r <= k:
                    DP[i][j][k] = j + r
                else:
                    DP[i][j][k] = DP[i-k][j][0]
            else:
                if i == j:
                    DP[i][j][k] = 2 * r
                else:
                    X = r
                    Y = C[j-1][i-1]
                    for i1 in range(i):
                        if 2*i-j > i1:
                            continue
                        p1 = (C[i][i1] * C[j-i-1][i-i1-1])/Y
                        if p1 < 0.00000000001:
                            continue
                        X += p1 * DP[i][j-i][i1]
                    DP[i][j][k] = X
                        
ans = 0.0
for i in range(n+1):
    p1 = (C[n][i] * C[d-1][n-i-1])/C[n+d-1][n-1]
    ans += p1 * DP[n][d][i]

print(ans)
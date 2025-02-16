from decimal import *
from tqdm import tqdm

with open("MAXN", "r") as f:
    MAX_N = int(f.readline())

getcontext().prec = MAX_N * 30

Cb = [[0 for _ in range(MAX_N + 1)] for _ in range(MAX_N + 1)]

for i in range(MAX_N + 1):
    Cb[i][0] = 1
    Cb[i][i] = 1
    for j in range(1, i):
        Cb[i][j] = Cb[i - 1][j - 1] + Cb[i - 1][j]


EV = [[Decimal("0") for _ in range(MAX_N + 1)] for _ in range(MAX_N + 1)]
DP = [[Decimal("0") for _ in range(MAX_N + 1)] for _ in range(MAX_N + 1)]
# DP[p][q] = sum_{i=0}^{q} qCi E[D^p D*^i]

EV[0][0] = Decimal("1.0")

print("[+] Calculating EVs...")
for p in tqdm(range(MAX_N + 1)):
    for q in range(MAX_N + 1):
        if (p - q) % 6 == 0:
            # target EV[p][q], EV[q][p]
            if p+q > 0:
                for i in range(p + 1):
                    if i < p:
                        EV[p][q] = EV[p][q] + (Cb[p][i] * DP[i][q])
                    else:
                        for j in range(q + 1):
                            if i == p and j == q: # d_{p,q}(i, j)
                                continue
                            if (i-j) % 6 == 0:
                                EV[p][q] = EV[p][q] + (Cb[p][i] * Cb[q][j]) * EV[i][j]
                EV[p][q] = EV[p][q] * Decimal(2) / Decimal(3 * (pow(2, p + q) - 1))

        for i in range(q + 1):
            DP[p][q] = DP[p][q] + Cb[q][i] * EV[p][i]

print("[+] Done!!")
import math

def pair2int(x, y, m, n):
    return x * n + y

def int2pair(XX, m, n):
    return XX // n, XX % n

while True:
    a, m, b, n = map(int, input().split())
    if not (a or b or m or n):
        break
    
    v = [[0] * (m * n) for _ in range(m * n + 1)]
    
    for i in range(m * n + 1):
        if i == 0:
            v[i][0] += 1
        else:
            for j in range(i + 1):
                j1, j2 = j, i - j
                index = pair2int(j1 % m, j2 % n, m, n)
                t = 1
                for x in range(i, i - j, -1):
                    t *= x
                for x in range(1, j + 1):
                    t //= x
                for x in range(j1 // m):
                    t *= a
                for x in range(j2 // n):
                    t *= b
                v[i][index] += t

    for i in range(m * n):
        if v[i][i] == 0:
            for j in range(i + 1, m * n):
                if v[i][j]:
                    for k in range(m * n + 1):
                        v[k][i] += v[k][j]
                    break
        for j in range(i + 1, m * n):
            t1, t2 = v[i][i], v[i][j]
            x = t1 // math.gcd(t1, t2)
            for k in range(m * n + 1):
                v[k][j] *= x
                v[k][j] -= (t2 // math.gcd(t1, t2)) * v[k][i]
        for j in range(i, m * n):
            G = v[0][j]
            for k in range(1, m * n + 1):
                G = math.gcd(G, v[k][j])
            for k in range(m * n + 1):
                v[k][j] //= G

    ans = [0] * (m * n + 1)
    for i in range(n * m - 1, -1, -1):
        for j in range(i + 1, m * n):
            v[n * m][i] -= v[j][i] * ans[j]
            v[j][i] = 0
        ans[i] = v[n * m][i] // v[i][i]

    ans[n * m] = -1
    print(*[-x for x in ans][::-1])
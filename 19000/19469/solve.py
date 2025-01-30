import sys

n = int(input())
if n == 1:
    print("!", 1)
    sys.stdout.flush()
    exit(0)
p = [0 for _ in range(n+1)]
for i in range(2, n+1):
    if p[i] == 0:
        for j in range(i, n+1, i):
            p[j] = i


ans = 1
for i in range(1, n+1):
    if p[i] == i:
        u = i
        while u*i <= n:
            u *= i
        ans *= u

print("?", ans-1)
sys.stdout.flush()
u = int(input())
print("!", u+1)
sys.stdout.flush()
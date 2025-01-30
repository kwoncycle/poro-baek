k, n = map(int, input().split())

for i in range(10000):
    for j in range(i+1, 10000):
        if i*i+j*j==k*i*j+1:
            print(i, j)

ab = [(1, k), (k, 1)]
q = [(1, k), (k, 1)]
while len(ab) < n and len(q) > 0:
    (a, b) = q[-1]
    q.pop()
    if 0<b*k-a<10**97:
        if (b, b*k-a) not in ab:
            ab.append((b, b*k-a))
            q.append((b, b*k-a))
        if (b*k-a, b) not in ab:
            ab.append((b*k-a, b))
            q.append((b*k-a, b))

print(len(ab))
input()
for _ in range(n):
    (a, b) = ab[_]
    c = (a+b)*k
    print(a, b, c)
    a, b = b, b*k-a
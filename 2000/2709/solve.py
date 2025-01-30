ans = [0, 1, 9, 89]
for i in range(4, 21):
    u = pow(10, i)
    u1 = pow(10, i-1)
    phi = 4 * pow(5, i-1)
    nxt = ans[-1]
    o = pow(2, nxt, u1)
    while o == pow(o, 1 + (phi//2), u1) and phi % 2 == 0:
        phi //= 2
    while o == pow(o, 1 + (phi//5), u1) and phi % 5 == 0:
        phi //= 5
    while not (1 <= (pow(2, nxt, u) // u1) <= 2):
        nxt += phi
    ans.append(nxt)

t = int(input())
for i in range(t):
    n = int(input())
    print(ans[n])
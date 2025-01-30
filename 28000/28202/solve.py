import sys
tt = int(input())
for _ in range(tt):
    n = int(sys.stdin.readline())
    x = len(str(n))
    u1 = (pow(10, x) - 1)//9
    u2 = (pow(10, x-1) - 1)//9
    ab = [u1*i for i in range(1,10)] + [u2*i for i in range(1,10)]
    #print(ab)
    find = 0
    for i in range(18):
        t = n - ab[i]
        if t <= 0:
            continue
        u = str(t)
        #print(t, u)
        truth = 1
        for j in u:
            if j != u[0]:
                truth = 0
                break
        if truth:
            print(t, ab[i])
            break

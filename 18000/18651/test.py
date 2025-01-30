m,a,c,x0,l1,r1,l2,r2 = map(int, input().split())

X = [x0]
for i in range(max(r1,r2)+5):
    X.append((a*X[-1]+c)%m)

sm = 0
for i in range(l1, r1+1):
    for j in range(l2, r2+1):
        sm += X[i]%(X[j]+1)

ans = str(sm)
print(ans)
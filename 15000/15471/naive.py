mp = dict()

def f(i, x, m):
    if (i,x,m) in mp:
        return mp[(i,x,m)]
    if x == 0 or x == i:
        mp[(i,x,m)] = 1
        return 1
    if i < x:
        mp[(i,x,m)] = 0
        return 0
    o1 = f(i-1, x-1, m)
    o2 = f(i-1, x, m)
    if (o1 + o2) % m == 0:
        mp[(i,x,m)] = 0
        return 0
    else:
        mp[(i,x,m)] = o1 + o2
        return o1 + o2
    
for i in range(40):
    for j in range(40):
        print(f(i,j,5), end = ' ')
    print()
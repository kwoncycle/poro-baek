t = int(input())

for _t in range(t):
    input()
    a, b, c, d = map(int, input().split())
    u = [a, b, c]
    u.sort()
    [a, b, c] = u
    if c - d >= b:
        c -= d
        print(a*b*c)
    elif (c-b) + 2*(b-a) >= d:
        d -= c-b
        c = b
        b -= d//2
        c -= d//2
        b -= d%2
        print(a*b*c)    
    else:
        d -= b-a
        b = a
        d -= c-a
        c = a
        a -= d//3
        b = a
        c = a
        d %= 3
        if d == 2:
            a -= 1
            b -= 1
        elif d == 1: 
            a -= 1
        print(a*b*c)
J = 2**5000 - 1

start = [0, 1]
n = int(input())
l = len(start)
d = 0
out = [0, 1]
while len(out) <= 10000:
    l = len(start)
    d += 1
    d1 = 10**d
    x = []
    for i in start:
        if (bin(i&J)[2:].zfill(5000))[-d-1:] == str(i).zfill(d+1):
            x.append(i)
    for i in start:
        i1 = d1 + i
        if (bin(i1&J)[2:].zfill(5000))[-d-1:] == str(i1).zfill(d+1):
            x.append(i1)
            out.append(i1)
    start = [xi for xi in x]

print(out[n])
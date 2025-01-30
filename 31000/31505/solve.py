import sys
from tqdm import tqdm

n = int(input())
a_str = sys.stdin.readline().rstrip()
b_str = sys.stdin.readline().rstrip()

a_str = (3000000 - len(a_str)) * '#' + a_str
b_str = (3000000 - len(b_str)) * '#' + b_str
a_str = 'TOC' * 1000000
b_str = 'TOC' * 1000000

a, b = 0, 0
am, bm = 0, 0
d = 100000
e = 3000000 // d
gd = pow(n, d)
g1000 = pow(n, 1000)

for i in tqdm(range(e)):
    a0 = 0
    for j in range(d*i, d*i+d, 1000):
        gj = 0
        for k in range(1000):
            if a_str[j+k] == '~':
                am = 1
                continue
            gj *= n
            gj += ord(a_str[j+k]) - 33
        
        a0 *= g1000
        a0 += gj
    a *= gd
    a += a0

for i in tqdm(range(e)):
    b0 = 0
    for j in range(d*i, d*i+d, 1000):
        gj = 0
        for k in range(1000):
            if b_str[j+k] == '~':
                bm = 1
                continue
            gj *= n
            gj += ord(b_str[j+k]) - 33
        
        b0 *= g1000
        b0 += gj
    b *= gd
    b += b0

t = a*b

arr = [0 for _ in range(2*e)]
for i in tqdm(range(2*e)):
    t, arr[i] = divmod(t, gd)

print(arr[0])
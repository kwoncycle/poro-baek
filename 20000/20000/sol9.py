from Crypto.Util.number import *
from gmpy2 import next_prime


f = open('challenge9.out', 'r')
o = f.read()
o = '[' + o + ']'
arr = eval(o)
#arr.sort()
#print(arr[:100])
print(max(arr))
#print(len(arr))

a1 = arr[2] - arr[1] / arr[1] - arr[0]
a2 = arr[3] - arr[2] / arr[2] - arr[1]
a3 = arr[4] - arr[3] / arr[3] - arr[2]

a1a2 = (arr[2] - arr[1]) * (arr[2] - arr[1]) - (arr[3] - arr[2]) * (arr[1] - arr[0])
a2a3 = (arr[3] - arr[2]) * (arr[3] - arr[2]) - (arr[4] - arr[3]) * (arr[2] - arr[1])

MOD = GCD(a1a2, a2a3)
A = (arr[2] - arr[1]) * pow(arr[1] - arr[0], -1, MOD) % MOD
C = (arr[1] - arr[0] * A) % MOD

print('MOD:', GCD(a1a2, a2a3))
print('A:', A)
print('C:', C)

st = 20000
for _ in range(20):
    print(st, end = ' ')
    st = (st * A + C) % MOD
print()

for _ in range(20):
    print(arr[_], end = ' ')

print()

# OUTPUT
# 1695307948
# MOD:  1695327975
# A:  754828306
# C:  460286996
# 20000 130789621 56895222 1644910028 545204689 1449899055 1139582426 350609377 384443808 1412330969 779969485 1484151231 305465507 1370922838 896003199 747279815 1661107261 1548293487 580083743 1188160579 
# 20000 130789621 56895222 1644910028 545204689 1449899055 1139582426 350609377 384443808 1412330969 779969485 1484151231 305465507 1370922838 896003199 747279815 1661107261 1548293487 580083743 1188160579 
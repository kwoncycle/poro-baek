from DecimalComplex import DecimalComplex
from decimal import Decimal

with open("MAXN", "r") as f:
    MAX_N = int(f.readline())

factorials = [1]
for i in range(1, MAX_N + 1):
    factorials.append(factorials[-1] * i)

coeff = [DecimalComplex(Decimal(1), Decimal(0))]
for n in range(1, MAX_N + 1):
    fct = 1
    for j in range(2*n - 3, 0, -2):
        fct *= j
    
    c = Decimal(pow(-1, n+1) * fct) / Decimal(pow(2, n)*factorials[n])
    coeff.append(DecimalComplex(c, Decimal(0)))
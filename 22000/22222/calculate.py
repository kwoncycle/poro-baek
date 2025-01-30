from getEVDP import *
from DecimalComplex import DecimalComplex
from Coeffs import *

def calculate_value(U : DecimalComplex, a : DecimalComplex):
    """
    Calculate E[ |U+aD| ] using Taylor
    """

    A = a / U
    B = a.conjugate() / U.conjugate()

    arrA = [DecimalComplex(Decimal(1), Decimal(0))]
    arrB = [DecimalComplex(Decimal(1), Decimal(0))]

    for i in range(1, MAX_N + 1):
        arrA.append(arrA[-1] * A)
        arrB.append(arrB[-1] * B)

    # we need sqrt(T) E[sqrt(1 + (AD + BD* + CDD*))]
    total = DecimalComplex(Decimal(0), Decimal(0))
    print("[+] Adding coeffs to calculate value", U, a)

    coeffA = [DecimalComplex(1, 0)]
    coeffB = [DecimalComplex(1, 0)]
    for n in range(1, MAX_N + 1):
        coeffA.append(coeff[n] * arrA[n])
        coeffB.append(coeff[n] * arrB[n])

    for i in tqdm(range(MAX_N + 1)):
        for j in range(MAX_N + 1):
            total = total + (coeffA[i] * coeffB[j] * DecimalComplex(EV[i][j], Decimal("0")))

    total = total * U.abs()

    return total

pi6 = DecimalComplex(Decimal(1) / Decimal(2), Decimal(3).sqrt()/Decimal(2))
P6 = [DecimalComplex(1, 0)]
for i in range(1, 6):
    P6.append(P6[-1] * pi6)

p1 = Decimal(1)/Decimal(3)
p2 = Decimal(1)/Decimal(9)

arr = [(DecimalComplex(0, 0), p1)]
for i in range(6):
    if i != 3:
        arr.append((P6[i], p2))

U = DecimalComplex(Decimal(1), Decimal(0))
a = DecimalComplex(Decimal(1), Decimal(0))

total = DecimalComplex(0, 0)
for U, p in arr:
    X = DecimalComplex(Decimal("0.5"), Decimal("0"))
    u = calculate_value(X + U*X*X, DecimalComplex(Decimal("0.25"), Decimal("0")))
    total = total + (u * DecimalComplex(p, Decimal("0")))

ans = total.real * Decimal("18") / Decimal("17") * Decimal("0.8")

print(ans, " is ans")
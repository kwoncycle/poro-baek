from decimal import Decimal, getcontext

getcontext().prec = 101

T = (Decimal("1") + Decimal("0.6").sqrt()) / Decimal("2")
T1 = Decimal("1")/T - Decimal("1")
x = -(T1.ln())
print(str(x))

Y = Decimal(1) / (Decimal(1) + (-x).exp())
print(Y)
print(T)

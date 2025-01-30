import sys
from fractions import Fraction
from typing import List, Sequence
from math import isqrt

class Vector(list):
    def __init__(self, x):
        super().__init__(map(Fraction, x))
    def sdot(self) -> Fraction:
        return self.dot(self)
    def dot(self, rhs: "Vector") -> Fraction:
        rhs = Vector(rhs)
        assert len(self) == len(rhs)
        return sum(map(lambda x: x[0] * x[1], zip(self, rhs)))
    def proj_coff(self, rhs: "Vector") -> Fraction:
        rhs = Vector(rhs)
        assert len(self) == len(rhs)
        return self.dot(rhs) / self.sdot()
    def proj(self, rhs: "Vector") -> "Vector":
        rhs = Vector(rhs)
        assert len(self) == len(rhs)
        return self.proj_coff(rhs) * self
    def __sub__(self, rhs: "Vector") -> "Vector":
        rhs = Vector(rhs)
        assert len(self) == len(rhs)
        return Vector(x - y for x, y in zip(self, rhs))
    def __mul__(self, rhs: Fraction) -> "Vector":
        return Vector(x * rhs for x in self)
    def __rmul__(self, lhs: Fraction) -> "Vector":
        return Vector(x * lhs for x in self)
    def __repr__(self) -> str:
        return "[{}]".format(", ".join(str(x) for x in self))

def gramschmidt(v: Sequence[Vector]) -> Sequence[Vector]:
    u: List[Vector] = []
    for vi in v:
        ui = Vector(vi)
        for uj in u:
            ui = ui - uj.proj(vi)

        if any(ui):
            u.append(ui)
    return u

def reduction(
    basis: Sequence[Sequence[int]], delta: Fraction = Fraction(3, 4)
) -> Sequence[Sequence[int]]:
    n = len(basis)
    basis = list(map(Vector, basis))
    ortho = gramschmidt(basis)

    def mu(i: int, j: int) -> Fraction:
        return ortho[j].proj_coff(basis[i])

    k = 1
    while k < n:
        for j in range(k - 1, -1, -1):
            mu_kj = mu(k, j)
            if abs(mu_kj) > Fraction(1, 2):
                basis[k] = basis[k] - basis[j] * round(mu_kj)
                ortho = gramschmidt(basis)

        if ortho[k].sdot() >= (delta - mu(k, k - 1) ** 2) * ortho[k - 1].sdot():
            k += 1
        else:
            basis[k], basis[k - 1] = basis[k - 1], basis[k]
            ortho = gramschmidt(basis)
            k = max(k - 1, 1)

    return [list(map(int, b)) for b in basis]

def icube(x):
    l, r, ans = 0, x, 0
    while l <= r:
        m = (l + r) // 2
        if m * m * m <= x:
            l, ans = m + 1, m
        else:
            r = m - 1
    return ans


mat = [[3,4,5,800001244100],[1,5,2,400000000000],[19,38,48,2124124124124],[10912381231231,0,0,61124124124124123]]
mat_L = reduction(mat)
print(mat_L)

input = sys.stdin.readline
N = int(input())
A = int(input())
B = int(input())

def find_left():
    l, r, ans = 0, N, 0
    while l <= r:
        m = (l + r) // 2
        if icube(m * m) < B:
            l = m + 1
        else:
            r, ans = m - 1, m
    return ans

L = find_left()

def is_answer(x):
    return x >= 1 and x <= N - 1 and x * x % N == A and icube(x * x) == B

def coppersmith(poly: List, mod: int, d: int):
    n = len(poly)
    pd = [d**i for i in range(n)]
    mat = [[poly[i] * pd[i] for i in range(n)]] + [
        [pd[i] * mod if i == j else 0 for i in range(n)] for j in range(n - 1)
    ]
    mat = reduction(mat)
    return [mat[0][i] // pd[i] for i in range(n)]

if N <= 100:
    for x in range(N):
        if is_answer(x):
            sys.stdout.write(f"{x}\n")
            exit(0)
else:
    d = int(N ** (1 / 3) / 6)
    while True:
        poly = [L * L - A, 2 * L, 1]
        reduced = coppersmith(poly=poly, mod=N, d=d)
        a, b, c = reduced[2], reduced[1], reduced[0]
        ans = []
        if a != 0:
            delta = b * b - 4 * a * c
            if delta >= 0:
                delta = isqrt(delta)
                ans = [(-b + delta) // (2 * a), (-b - delta) // (2 * a)]
        elif b != 0:
            ans = [-c // b]
        for x in ans:
            if is_answer(L + x):
                sys.stdout.write(f"{L + x}\n")
                exit(0)
        L = L + d
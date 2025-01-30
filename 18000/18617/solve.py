import sys
from fractions import Fraction
from typing import List, Sequence

class Vector(list):
    def __init__(self, x):
        super().__init__(map(Fraction, x))
    def sdot(self) -> Fraction:
        return self[0]*self[0] + self[1]*self[1]
    def dot(self, rhs: "Vector") -> Fraction:
        rhs = Vector(rhs)
        #assert len(self) == len(rhs)
        return self[0]*rhs[0] + self[1]*rhs[1]
    def proj_coff(self, rhs: "Vector") -> Fraction:
        rhs = Vector(rhs)
        #assert len(self) == len(rhs)
        return self.dot(rhs) / self.sdot()
    def proj(self, rhs: "Vector") -> "Vector":
        rhs = Vector(rhs)
        #assert len(self) == len(rhs)
        return self.proj_coff(rhs) * self
    def __sub__(self, rhs: "Vector") -> "Vector":
        rhs = Vector(rhs)
        #assert len(self) == len(rhs)
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
    basis = list(map(Vector, basis))
    ortho = gramschmidt(basis)

    while True:
        if abs(basis[0][0]) <= 1000000000 and abs(basis[0][1]) <= 1000000000:
            break
        mu_kj = ortho[0].proj_coff(basis[1])
        if abs(mu_kj) > Fraction(1, 2):
            basis[1] = basis[1] - basis[0] * round(mu_kj)
            #ortho = gramschmidt(basis)

        basis[1], basis[0] = basis[0], basis[1]
        ortho = gramschmidt(basis)

    return [list(map(int, b)) for b in basis]

p1 = 2897723681
p2 = 3133144633
p1_i = pow(p1, -1, p2)
p2_i = pow(p2, -1, p1)
M = p1* p2
input = sys.stdin.readline
Flush = sys.stdout.flush
#from tqdm import tqdm

t = int(input())
for _ in (range(t)):
    print("?", p1)
    Flush()
    u1 = int(input())
    #u1 = 1217778274
    print("?", p2)
    Flush()
    u2 = int(input())
    #u2 = 1440370218
    u = u1*p2_i*p2 + u2*p1_i*p1
    u %= M

    mat = [[1, u], [0, M]]
    mat_L = reduction(mat)
    q, p = mat_L[0][0], mat_L[0][1]
    if p < 0:
        p *= -1
        q *= -1
    
    assert u1*q%p1 == p
    assert u2*q%p2 == p
    assert 1 <= p <= 1000000000
    assert 1 <= q <= 1000000000

    print("!", p, q)
    Flush()
from decimal import Decimal, ROUND_HALF_EVEN

precision = Decimal("1.000000000000000")

class DecimalComplex:
    def __init__(self, real : Decimal, imag : Decimal):
        self.real = real
        self.imag = imag
    
    def __add__(self, other):
        if isinstance(other, DecimalComplex):
            return DecimalComplex(self.real + other.real, self.imag + other.imag)
        raise TypeError("Unsupported operand type for +")
    
    def __sub__(self, other):
        if isinstance(other, DecimalComplex):
            return DecimalComplex(self.real - other.real, self.imag - other.imag)
        raise TypeError("Unsupported operand type for -")
    
    def __mul__(self, other):
        if isinstance(other, DecimalComplex):
            real_part = self.real * other.real - self.imag * other.imag
            imag_part = self.real * other.imag + self.imag * other.real
            return DecimalComplex(real_part, imag_part)
        raise TypeError("Unsupported operand type for *")
    
    def __truediv__(self, other): # probably not be used
        if isinstance(other, DecimalComplex):
            denom = other.real**2 + other.imag**2
            real_part = (self.real * other.real + self.imag * other.imag) / denom
            imag_part = (self.imag * other.real - self.real * other.imag) / denom
            return DecimalComplex(real_part, imag_part)
        raise TypeError("Unsupported operand type for /")
    
    def conjugate(self):
        return DecimalComplex(self.real, -self.imag)
    
    def abs(self):
        return DecimalComplex((self.real**2 + self.imag**2).sqrt(), Decimal(0))
    
    def __repr__(self):
        return f"({self.real.quantize(precision)} + {self.imag.quantize(precision)}j)"
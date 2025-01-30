s = []
def U():
    s.append('U')
def D():
    s.append('D')
def L():
    s.append('L')
def R():
    s.append('R')

def u():
    s.append('u')
def d():
    s.append('d')
def l():
    s.append('l')
def r():
    s.append('r')

def F():
    s.append('F')

R()
D()
for i in range(7):
    for j in range(14):
        d()
        F()
        d()
    R()
    U()
    for j in range(14):
        u()
        F()
        u()
    R()
    if i < 6:
        D()

for i in range(15):
    l()
    F()
    l()
for i in range(15):
    d()
    F()
    d()
for i in range(15):
    r()
    F()
    r()
for i in range(15):
    u()
    F()
    u()

print(''.join(s))
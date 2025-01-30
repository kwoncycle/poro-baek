from pwn import *
from string import ascii_lowercase, ascii_uppercase
import random

while True:
    s = "".join([random.choice(ascii_uppercase + ascii_lowercase) for _ in range(5)])
    n = len(s)
    t = random.choice(ascii_uppercase)
    if t not in s:
        continue
    nc = process("./solve")
    nc.sendline(str(n) + " " + t)
    nc.sendline(s)
    o = nc.recvline()
    print(str(n) + " " + t + " " + s)
    print(o)
    nc.close()
    input()
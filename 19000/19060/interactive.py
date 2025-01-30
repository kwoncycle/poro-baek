from pwn import *

n = int(input())
nc = process(["./solve"])

p = [i for i in range(n)]#[5,4,2,0,3,1]
pi = [0 for _ in range(n)]
#pi = [1,3,0,2,5,6]
for i in range(n):
    pi[p[i]] = i
nc.sendline(str(n))
while True:
    l = nc.recvline()
    #print(l)
    #print(l, end = ' ')
    if l[0] == ord('!'):
        o = list(map(int, l.split()[1:]))
        if o == pi:
            print('good')
        else:
            print('fuck')
            #print(p)
            #print(o)
           # print(l)
        break
    l = list(map(int, l.split()[1:]))
    #print(str(pi[(p[l[0]]*p[l[1]]+p[l[2]])%n]))
    nc.sendline(str(pi[(p[l[0]]*p[l[1]]+p[l[2]])%n]))
nc.interactive()
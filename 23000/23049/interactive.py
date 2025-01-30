from pwn import *

for N in range(640001, 1000001):
    nc = process(["./solve"])
    nc.sendline('1')
    nc.recvline()
    nc.sendline('1')

    while True:
        l = nc.recvline().decode()
        if l[0] == '!':
            #nc.sendline('0')
            if N != int(l.split()[1]):
                print('WTF', N)
                print(l)
                exit(0)
            else:
                print('==========    ',N, end = '     ===========')
                
            break
        
        [x, y] = list(map(int,l.split()[1:]))
        ans = 1+y%N
        nc.sendline(str(ans))
        
    nc.close()
    
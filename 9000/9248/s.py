from random import randint

for i in range(200000):
    print(chr(ord('a')+randint(12, 1234)%26), end='')
#print('a'*500000)
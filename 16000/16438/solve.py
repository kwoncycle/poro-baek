n = int(input())
for xx in range(7):
    if (n-1).bit_length() <= xx:
        x = 0
    else:
        x = xx
    for i in range(n):
        if (i // (1<<(x)))%2 == 1:
            print('A',end='')
        else:
            print('B',end='')
    print()
        
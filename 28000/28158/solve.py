n = int(input())

MOD2 = 2**18
MOD5 = 5**18

fct2 = [1 for _ in range(1000015)]
fct5 = [1 for _ in range(1000015)]
fct2_cnt = [0 for _ in range(1000015)]
fct5_cnt = [0 for _ in range(1000015)]
fct2_inv = [1 for _ in range(1000015)]
fct5_inv = [1 for _ in range(1000015)]

for i in range(1, 1000013):
    i2 = i
    i5 = i
    cnt2 = 0
    cnt5 = 0
    while i2 % 2 == 0:
        i2 //= 2
        cnt2 += 1
    while i5 % 5 == 0:
        i5 //= 5
        cnt5 += 1
    
    fct2[i] = fct2[i-1] * i2 % MOD2
    fct2_cnt[i] = fct2_cnt[i-1] + cnt2
    fct5[i] = fct5[i-1] * i5 % MOD5
    fct5_cnt[i] = fct5_cnt[i-1] + cnt5

    fct2_inv[i] = pow(fct2[i], -1, MOD2)
    fct5_inv[i] = pow(fct5[i], -1, MOD5)


if n <= 3:
    ans2 = 1
    ans5 = 1
else:
    ans2 = 1
    ans5 = 1
    pi = 314159265358979
    index = 0
    for i in range(4, n+1):
        if (index+1) * pi <= i * 100000000000000:
            index += 1
            # n-i+index C index
            M2_arr = [fct2[n-i+index] * fct2_inv[index] * fct2_inv[n-i] % MOD2, fct2_cnt[n-i+index] - fct2_cnt[index] - fct2_cnt[n-i]]
            M2 = 1
            if M2_arr[1] >= 18:
                M2 = 0
            else:
                M2 = pow(2, M2_arr[1]) * M2_arr[0] % MOD2

            M5_arr = [fct5[n-i+index] * fct5_inv[index] * fct5_inv[n-i] % MOD5, fct5_cnt[n-i+index] - fct5_cnt[index] - fct5_cnt[n-i]]
            M5 = 1
            if M5_arr[1] >= 18:
                M5 = 0
            else:
                M5 = pow(5, M5_arr[1]) * M5_arr[0] % MOD5
            
            ans2 += M2
            ans5 += M5
            

A = ans2 * MOD5 * pow(MOD5, -1, MOD2) + ans5 * MOD2 * pow(MOD2, -1, MOD5)
A %= (MOD2*MOD5)
print(A)
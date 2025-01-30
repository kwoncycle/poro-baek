# Code from yyyy7089

def failure(S):
    sl = len(S)
    f = [0] * sl
    i = 1; j = 0 #i = check (current) index; j = length
    while i < sl:
        if S[j] == S[i]:
            f[i] = j + 1
            i += 1
            j += 1
        elif j > 0:
            j = f[j-1]
        else:
            i += 1
    return f

def kmp(F, S):
    fl = len(F)
    sl = len(S)
    if fl > sl:
        return []
    i = 0; j = 0 # i = current index, j = length found
    L = []
    while i < sl:
        if F[j] == S[i]:
            i += 1
            j += 1
            if j == fl:
                L.append(i-j+1)
                j -= fl - fl_f
        else:
            if j > 0:
                j = failure_list[j-1]
            else:
                i += 1
    return L

s = input()
f = input()
failure_list = failure(f)
fl_f = failure(f)[-1]
L = kmp(f, s)
print(len(L))
for i in L:
    print(i,end=' ')
print()
import sys
input = sys.stdin.read

X = input()
X.replace('\n', ' ')
X = X.split()
index = 0
cnt = 1
while True:
    try:
        n = int(X[index])
        #first = [*map(int, input().rstrip().split())]
        #second = [*map(int, input().rstrip().split())]
        score_f = []
        score_s = []
        index += 1
        first = [int(X[index + i]) for i in range(n)]
        index += n
        second = [int(X[index + i]) for i in range(n)]
        index += n
        for i in range(n):
            score_f.append((first[i], i + 1))
        for i in range(n):
            score_s.append((second[i], i + 1))

        score_f.sort(reverse = True)
        score_s.sort(reverse = True)
        res = -1
        for i in range(n):
            if score_f[i][1] != score_s[i][1]:
                res = i + 1
                break
        if res < 0:
            print(f'Case {cnt}: agree')
        else:
            print(f'Case {cnt}: {res}')
        cnt += 1
        if index >= len(X):
            break
    except ValueError:
        break
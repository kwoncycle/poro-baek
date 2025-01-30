def solve(N, M, Map):
    DP = [[0 for _ in range(N+1)] for __ in range(N+1)] # 0으로 초기화된 (N + 1) x (N + 1) 크기의 DP 배열 선언
    DP[1][1] = 1 % M # 시작점 설정

    # '.'은 빈칸 '#'은 벽
    for r in range(1, N+1):
        for c in range(1, N+1):
            if Map[r][c] == '#':
                continue

            if r + 1 <= N and Map[r + 1][c] == '.':
                DP[r + 1][c] = (DP[r + 1][c] + DP[r][c]) % M # 이동 방법 1

            if c + 1 <= N and Map[r][c + 1] == '.':
                DP[r][c + 1] = (DP[r][c + 1] + DP[r][c]) % M # 이동 방법 2

            if r + 2 <= N and (Map[r + 1][c] == '.' and Map[r + 2][c] == '.'):
                DP[r + 2][c] = (DP[r + 2][c] + DP[r][c]) % M # 이동 방법 3

    assert DP[N][N] == 0
    if DP[N][N] == 0:
        DP[N][N] = -1

    return DP[N][N]


M = int(input())
N = int(input())


Map = [[0 for _ in range(N+1)] for __ in range(N+1)]
for i in range(N):
    s = input()
    for j in range(N):
        Map[i+1][j+1] = s[j]

solve(N, M, Map)
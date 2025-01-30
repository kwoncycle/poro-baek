# x^2 - ay^2 = 1
# x_k+1 = x1x_k + ny_1y_k
# y_k+1 = x_1y_k + y_1 x_k
n = int(input())
u100_1 = pow(100, n)
u100_2 = pow(100, n+1)

K = 2
ans2 = [(3, 2)]
for i in range(10000):
    u1 = ans2[0][0]*ans2[i][0] + K * ans2[0][1]*ans2[i][1]
    u2 = ans2[0][0]*ans2[i][1] + ans2[0][1]*ans2[i][0]
    ans2.append((u1, u2))
    (u1, u2) = ans2[i]
    if u100_1 <= u1*u1-1 < u100_2:
        print(u2//2, 2)
        print(u1, 1)
        break
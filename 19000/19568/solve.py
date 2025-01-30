arr = [[0 for i in range(30)] for _ in range(30)]
#14 14
for i in range(14):
    arr[i][14] = 1
for i in range(15, 30):
    arr[i][14] = 15
for i in range(14):
    arr[14][i] = 225
for i in range(15, 30):
    arr[14][i] = 3375

for i in range(30):
    for j in range(30):
        print(arr[i][j], end = ' ')
    print()
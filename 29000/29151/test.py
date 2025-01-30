from tqdm import tqdm

for MM in range(1, 6):
    input()
    cnt = 0
    babamba = dict()
    bibimbap = []
    index = 0
    for i in range(MM**MM):
        arr = [0 for _ in range(MM)]
        for j in range(MM):
            arr[j] = i%MM
            i //= MM
        for j in range(MM-1):
            break
        truth = 1
        for j in range(MM-1):
            if arr[j] == arr[j+1]:
                truth = 0
                break
        check = [0 for _ in range(MM)]
        end = 0
        for j in range(MM):
            if check[arr[j]]:
                continue
            if arr[j] == end:
                check[arr[j]] = 1
                end += 1
            else:
                truth = 0
                break
        cnt += truth
        if truth:
            print(arr)
            babamba[tuple(arr)] = index
            index += 1
            bibimbap.append(tuple(arr))


    arr = [[0 for _ in range(cnt)] for i in range(cnt)]
    indexing = [0 for _ in range(16**MM)]
    for j in tqdm(range(16**MM)):
        t = hex(j)[2:].zfill(MM)
        truth = 1
        for r in range(MM-1):
            if t[r] == t[r+1]:
                truth = 0
                break
        if truth == 0:
            indexing[j] = -1
            continue
        check = [-1 for _ in range(16)]
        index = 0
        out = [0 for _ in range(MM)]
        for r in range(MM):
            if check[int(t[r], 16)] == -1:
                check[int(t[r], 16)] = index
                index += 1
            out[r] = check[int(t[r], 16)]
        i1 = babamba[tuple(out)]
        indexing[j] = i1

    for i in (range(cnt)):
        X = bibimbap[i]
        for j in tqdm(range(16**MM)):
            t = hex(j)[2:].zfill(MM)
            truth = 1
            for r in range(MM):
                if X[r] == int(t[r], 16):
                    truth = 0
                    break
            if truth == 0:
                continue
            i1 = indexing[j]
            if i1 == -1:
                continue
            arr[i][i1] += 1

    print(arr)
    print(cnt)
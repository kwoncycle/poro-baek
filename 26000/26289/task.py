fct = [1 for _ in range(5983)]
for i in range(1, 5983):
    fct[i] = fct[i-1] * i

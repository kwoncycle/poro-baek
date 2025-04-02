import sys

lines = sys.stdin.readlines()

for line in lines:
    t, a, b = map(int, line.split())
    print("(" + str(t) + "^" + str(a) + "-1)/(" + str(t) + "^" + str(b) + "-1) ", end = '')
    if t == 1:
        #print("0")
        print("is not an integer with less than 100 digits.")
    elif a % b != 0:
        print("is not an integer with less than 100 digits.")
    else:
        if a == b:
            print("1")
        else:
            if a-b > 400:
                print("is not an integer with less than 100 digits.")
            else:
                u = (pow(t, a) - 1) // (pow(t, b) - 1)
                if len(str(u)) >= 100:
                    print("is not an integer with less than 100 digits.")
                else:
                    print(u)
                
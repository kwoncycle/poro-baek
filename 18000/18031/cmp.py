o1 = open('./output/C_6', 'r')
o2 = open('./output1/C_6', 'r')

r1 = o1.readlines()
r2 = o2.readlines()
for i in range(len(r1)):
    if r1[i] != r2[i]:
        if(i < 100):
            print(r1[i].rstrip(), r2[i].rstrip(), i)
print(r1 == r2)
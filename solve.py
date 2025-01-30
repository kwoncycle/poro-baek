from math import gcd
n=int(input())
li=[list(map(int,input().split())) for i in range(n)]
for i in range(n):
    for j in range(n):
        x=li[0][i]*li[j][0]
        y=li[0][0]*li[j][i]
        if(x!=y):print(-1);exit(0)
di={}
for i in range(n):
    for j in range(n):
        x=li[0][i]
        y=li[j][0]
        g=gcd(x,y)
        x//=g
        y//=g
        if((x,y) not in di):di[(x,y)]=0
        di[(x,y)]+=1
x=0
a1,a2=0,0
for i in di:
    if(di[i]>x):x=di[i];a1,a2=i
l=set([(a1,1),(a2,1)])
for i in range(1,n):
    x,y=a1*li[0][0],li[0][i]
    g=gcd(x,y)
    l.add((x//g,y//g))
for i in range(1,n):
    x,y=a2*li[0][0],li[i][0]
    g=gcd(x,y)
    l.add((x//g,y//g))
print(len(l))
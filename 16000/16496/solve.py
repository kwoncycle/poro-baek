n=int(input())
a=list(map(int,input().split()))
a.sort(key=lambda x:x*10**30/(10**(len(str(x)))-1))
if a[-1]==0:print(0)
else:
 for i in a[::-1]:print(i,end='')
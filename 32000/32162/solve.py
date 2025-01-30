import sys
I=sys.stdin.readline
A=[0]
for i in range(1,200000):
 c=0;i1=i
 while i%3==0:
  i//=3;c+=1
 while i%5==0:
  i//=5;c-=1
 if c%3==0:
  A.append(i1)
T=int(I())
while T:
 print(A[int(I())]);T-=1
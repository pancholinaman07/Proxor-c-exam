greedily examine bits in target from low to high using smaller numbers in A first

A=[1,1,32]
B=6

B=[1<<i for i in range(32,-1,-1) if (B>>i)&1]
A=sorted(A)[::-1] # or without sort, loop from bit 1 to 32

cur=res=0

while A and B:
    if cur>=B[-1]:
        cur-=B.pop()
        continue
       
    if A[-1]+cur>=B[-1]:
        while A[-1]>B[-1]:
            res+=1
            A+=[A.pop()>>1]*2
   
    cur+=A.pop()
       
return  res 

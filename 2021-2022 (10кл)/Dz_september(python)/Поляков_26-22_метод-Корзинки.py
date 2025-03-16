n,k = map(int, input().split())
b = [0]*1000

for i in range(n):
	b[int(input())-1]+=1

nac=0
kon=0
naci=-1
koni=-1
max=0
sum=0
kol=0

for i in range(1000):
	if nac!=k and kon!=k:
		if b[i]!=0:
			b[i]=0
			nac=nac+1
			
		if b[-i-1]!=0:
			b[-i-1]=0
			kon=kon+1
	
	elif nac==k and kon!=k:
		if b[-i-1]!=0:
			b[-i-1]=0
			kon=kon+1
		
		if naci==-1:
			naci=i
	
	elif nac!=k and kon==k:
		if b[i]!=0:
			b[i]=0
			nac=nac+1
		
		if koni==-1:
			koni=999-i
	
	elif nac==kon==k:
		if naci==-1:
			naci=i
		
		if koni==-1:
			koni=999-i
		
		for j in range(naci,koni+1):
			if b[j]!=0:
				max=j
			
			if b[j]!=0:
				sum=sum+j
				kol=kol+1

print(max, sum/kol)

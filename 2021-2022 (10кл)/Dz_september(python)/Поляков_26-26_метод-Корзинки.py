n = int(input())
b = [0]*100
s = 0

for i in range(n):
	b[int(input())-1]+=1

for i in range(0,50):
	s=s+min(b[i], b[-i-1])

print(s)

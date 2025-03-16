n = int(input())
a = [int(input()) for i in range(n)]
s = 0
for i in a:
	for j in a[a.index(i)+1:]:
		if i+j==100:
			s+=1
print(s)

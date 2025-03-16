n,k = map(int, input().split())
a = [int(input()) for i in range(n)]
for i in range(k):
	a.pop(a.index(max(a)))
	a.pop(a.index(min(a)))
print(max(a), int(sum(a)/len(a)))

'''n=int(input())
b=[0]*8
bfor=[0]*8
s=''
s1 = -1
s2 = -1

for i in range(n):
	s=input()
	s1=int(s[:s.find(' ')])
	s2=int(s[s.find(' ')+1:])
	for j in range(8):
		if s1+bfor[j] > b[(s1+bfor[j])%8]:
			b[(s1+bfor[j])%8] = bfor[j]+s1
		
		if s2+bfor[j] > b[(s2+bfor[j])%8]:
			b[(s2+bfor[j])%8] = bfor[j]+s2
	
	bfor=[i for i in b]
print(b[3])'''
#Моя попытка, потом, после подсказки от учителя, сделал программу по-другому

'''
6
1 3
5 12
6 9
5 4
3 3
5 1

=35
'''

n=int(input())
t=[0]*8
for i in range(n):
	s=input()
	s1=int(s[:s.find(' ')])
	s2=int(s[s.find(' ')+1:])
	j = 0
	k = 0
	a=[0]*8
	b=[0]*8
	while j!=8 and k!=-1:
		if t[j]!=0:
			summ=s1+t[j]
			ost=summ%8
			a[ost]=summ
			summ=s2+t[j]
			ost=summ%8
			b[ost]=summ
		
		elif t[j]==0:
			if sum(t)==0:
				if s1%8==s2%8:
					a[s1%8]=max(s1,s2)
				
				else:
					a[s1%8]=s1
					a[s2%8]=s2
				k = -1
		j+=1
	
	for g in range(8):
		if a[g]==0:
			t[g]=b[g]
		elif b[g]==0:
			t[g]=a[g]
		elif a[g]!=0 and b[g]!=0:
			t[g] = max(a[g],b[g])

if t[3]==0:
	print('Нет такой суммы, что её запись в восьмеричной системе счисления оканчивается на 3')
if t[3]!=0:
	print(t[3])

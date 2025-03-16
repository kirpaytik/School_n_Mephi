n=int(input())
t=[0]*16
for i in range(n):
	s=input()
	s1=int(s[:s.find(' ')])
	s2=int(s[s.find(' ')+1:])
	j = 0
	l = 0
	a=[0]*16
	b=[0]*16
	while j!=16 and k!=-1:
		if t[j]!=0:
			summ=s1+t[j]
			ost=summ%16
			a[ost]=summ
			summ=s2+t[j]
			ost=summ%16
			b[ost]=summ
		
		elif t[j]==0:
			if sum(t)==0:
				if s1%16==s2%16:
					a[s1%16]=min(s1,s2)
				
				else:
					a[s1%16]=s1
					a[s2%16]=s2
				k = -1
		j+=1
	
	for g in range(16):
		if a[g]==0:
			t[g]=b[g]
		elif b[g]==0:
			t[g]=a[g]
		elif a[g]!=0 and b[g]!=0:
			t[g] = min(a[g],b[g])

if t[15]==0:
	print('Нет такой суммы, что её запись в шестнадцатиричной системе счисления оканчивается на F')
if t[15]!=0:
	print(t[15])

'''
6
3 5
5 12
6 9
5 4
7 9
5 1

=31
'''

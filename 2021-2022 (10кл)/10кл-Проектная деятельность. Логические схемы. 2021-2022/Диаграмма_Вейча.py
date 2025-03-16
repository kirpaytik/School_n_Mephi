n = int(input())
diagVei4a = []
jdiagVei4a = 2**(n//2) + 2 if n%2==0 else 2**(n//2+1) + 2
for i in range(2**(n//2) + 2):
    diagVei4a.append([0]*jdiagVei4a)
diagVei4a[0][0] = ''
diagVei4a[-1][0] = ''
diagVei4a[0][-1] = ''
diagVei4a[-1][-1] = ''

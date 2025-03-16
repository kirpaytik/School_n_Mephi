a = str(input())
if ord(a[0])>96 and ord(a[0])<123:
	b = chr(ord(a[0])-32) + a[1:]
else:
	b = a
print(b)

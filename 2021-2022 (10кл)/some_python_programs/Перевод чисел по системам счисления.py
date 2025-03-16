a = str(input('Введите число: '))
ok = 1
for i in range(len(a)):
	if i == 0:
		if '1234567890abcdefghijklmnopqrstuvwxyz-+'.find(a[i]) == -1:
			ok = 0
	else:
		if '1234567890abcdefghijklmnopqrstuvwxyz'.find(a[i]) == -1:
			ok = 0
if ok == 0:
	print('Ошибка: введены символы такие/так, что невозможно составить число')
else:
	n1 = int(input('Введите основание данного числа: '))
	n2 = int(input('Введите основание искомого числа: '))
	s = []
	k = 1
	for i in range(len(a)):
		s.append(a[i])
	for i in range(len(s)):
		if '0123456789'.find(s[i]) == -1:
			if ord(s[i]) < 95:
				s[i] = ord(s[i]) - 55
			elif ord(s[i]) > 95:
				s[i] = ord(s[i]) - 87
		s[i] = int(s[i])
	for i in range(len(a)):
		if s[i] >= n1:
			k = 0
	if k == 0:
		print()
		print('Ошибка ввода. Введено невозмножное число для его основания.')
	elif k == 1:
		if n1 != 10:
			t = 0
			b = 0
			for i in reversed(s):
				b = b + (n1**t)*i
				t += 1
		elif n1 == 10:
			b = ''
			for i in range(len(s)):
				b = b + str(s[i])
		if n2 != 10:
			b = int(b)
			if b == 0:
				z = 0
			elif b != 0:
				z = ''
			while b != 0:
				c = b % n2
				if c > 9:
					c = chr(c + 55)
				z = str(c) + z
				b //= n2
		if n2 == 10:
			z = b
		print()
		print('Число ', a, ', данное в ', n1, '-чной системе счисления, переведённое в ', n2, '-чную систему счисления - ', z, '.', sep='')

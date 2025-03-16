def parallelnost(z12, z34, parall1234):
	if z12[0] == 'x' and z34[0] == 'x':                     # Если уравнение вида "x = b"
		parall1234 = 'Параллельны'
	elif z12[0] == 'y' and z34[0] == 'y':
		if z12.find('x') == -1 and z34.find('x') == -1:     # Если уравнение вида "y = a"
			parall1234 = 'Параллельны'
		elif z12.find('x') != -1 and z34.find('x') != -1:   # Если уравнение вида "y = kx + b"
			if z12[z12.find('=') : z12.find('x')] == z34[z34.find('=') : z34.find('x')]:       # Если коэффициенты k равны
				parall1234 = 'Параллельны'
			elif z12[z12.find('=') : z12.find('x')] != z34[z34.find('=') : z34.find('x')]:     # Если коэффициенты k не равны
				parall1234 = 'Не параллельны'
			else:
				parall1234 = 'Не параллельны'
		else:
			parall1234 = 'Не параллельны'
	elif (z12.find('x') == -1 and z34.find('x') != -1) or (z12.find('x') != -1 and z34.find('x') == -1):
			parall1234 = 'Не параллельны'
	elif (z12[0] == 'x' and z34[0] == 'y') or (z12[0] == 'y' and z34[0] == 'x'):
		parall1234 = 'Не параллельны'
	else:
		parall1234 = 'Не параллельны'
	return parall1234

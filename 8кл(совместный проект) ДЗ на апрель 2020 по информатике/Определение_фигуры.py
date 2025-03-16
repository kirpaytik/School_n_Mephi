A = str(input('Введите значение координаты 1 точки  сначала по x, затем по y, разделив значения пробелом'))
B = str(input('Введите значение координаты 2 точки  сначала по x, затем по y, разделив значения пробелом'))
C = str(input('Введите значение координаты 3 точки  сначала по x, затем по y, разделив значения пробелом'))
D = str(input('Введите значение координаты 4 точки  сначала по x, затем по y, разделив значения пробелом'))

ax = int( A[0 : A.find(' ')] )
bx = int( B[0 : B.find(' ')] )
cx = int( C[0 : C.find(' ')] )
dx = int( D[0 : D.find(' ')] )

ay = int( A[A.find(' ')+1 : ] )
by = int( B[B.find(' ')+1 : ] )
cy = int( C[C.find(' ')+1 : ] )
dy = int( D[D.find(' ')+1 : ] )

def yravneniepryamoi(x1,x2,y1,y2,z):
    if x1==0 and x2==0:
        z = 'x=0'
    elif y1==0 and y2==0:
        z = 'y=0'
    else:
        k = (y1-y2)/(x1-x2)
        b = y2 - k*x2
        if k%1==0:
            k = int(k)
        if b%1==0:
            b = int(b)
        k = str(k)
        if k=='1':
            k = ''
        if k=='-1':
            k = '-'
        
        if k=='0':
            b = str(b)
            z = 'y=' + b
        elif k!=0:
            if b>0:
                b = str(b)
                b = '+' + b
            elif b==0:
                b = ''
            elif b<0:
                b = str(b)
            z = 'y=' + k + 'x' + b
    return z

if A!=B and A!=C and A!=D and B!=C adn B!=D and C!=D:     # Если все точки не совпадают
	if ax == bx:
		if cx != ax:
			Kkoefac = (ay - cy)/(ax - cx)
			Bkoefac = ay - KkoefAC * ax
			Kkoefbc = (by - cy)/(bx - cx)
			Bkoefbc = by - KkoefBC * bx
			if (dx != ax) and (dy != Kkoefac * dx + Bkoefac) and (dy != Kkoefbc * dx + Bkoefbc):
				figure = 'Четырёхугольник'
			elif (dx == ax) or (dy == Kkoefac * dx + Bkoefac) or (dy == Kkoefbc * dx + Bkoefbc):
				figure = 'Треугольник'
		elif cx == ax:
			if dx != ax:
				figure = 'Треугольник'
			elif dx == ax:
				figure = 'Отрезок'
	elif ax != bx:
		Kkoefab = (ay - by)/(ax - bx)
		Bkoefab = ay - KkoefAB * ax
		if cy != Kkoefab * cx + Bkoefab:
			if cx == ax:
				Kkoefbc = (by - cy)/(bx - cx)
				Bkoefbc = by - KkoefBC * bx
				if (dx != ax) and (dy != Kkoefab * dx + Bkoefab) and (dy != Kkoefbc * dx + Bkoefbc):
					figure = 'Четырёхугольник'
				elif (dx == ax) or (dy == Kkoefab * dx + Bkoefab) or (dy == Kkoefbc * dx + Bkoefbc):
					figure = 'Треуголник'
			elif cx != ax:
				Kkoefac = (ay - cy)/(ax - cx)
				Bkoefac = ay - KkoefAC * ax
				if cx == bx:
					if (dy != Kkoefab * dx + Bkoefab) and (dy != Kkoefac * dx + Bkoefac) and (dx != bx):
						figure = 'Четырёхугольник'
					elif (dy == Kkoefab * dx + Bkoefab) or (dy == Kkoefac * dx + Bkoefac) or (dx == bx):
						figure = 'Треугольник'
				elif cx != bx:
					Kkoefbc = (by - cy)/(bx - cx)
					Bkoefbc = by - KkoefBC * bx
					if (dy != Kkoefab * dx + Bkoefab) and (dy != Kkoefac * dx + Bkoefac) and (dy != Kkoefbc * dx + Bkoefbc):
						figure = 'Четырёхугольник'
					elif (dy == Kkoefab * dx + Bkoefab) or (dy == Kkoefac * dx + Bkoefac) or (dy == Kkoefbc * dx + Bkoefbc):
						figure = 'Треугольник'
		elif cy == Kkoefab * cx + Bkoefab:
			if dy != Kkoefab * dx + Bkoefab:
				figure = 'Треугольник'
			elif dy == Kkoefab * dx + Bkoefab:
				figure = 'Отрезок'
elif A==B or A==C or A==D or B==C or B==D or C==D:      # Если совпадают 2 точки
	if A == B:                                          # 1 из 6
		if ax == cx:
			if dx != ax:
				figure = 'Треугольник'
			elif dx == ax:
				figure = 'Отрезок'
		elif ax != cx:
			Kkoefac = (ay - cy)/(ax - cx)
			Bkoefac = ay - Kkoefac * ax
			if dy != Kkoefac * dx + Bkoefac:
				figure = 'Треугольник'
			elif dy == Kkoefac * dx + Bkoefac:
				figure = 'Отрезок'
	elif A == C:                                        # 2 из 6
		if ax == bx:
			if dx != ax:
				figure = 'Треугольник'
			elif dx == ax:
				figure = 'Отрезок'
		elif ax != bx:
			Kkoefab = (ay - by)/(ax - bx)
			Bkoefab = ay - Kkoefab * ax
			if dy != Kkoefab * dx + Bkoefab:
				figure = 'Треугольник'
			elif dy == Kkoefab * dx + Bkoefab:
				figure = 'Отрезок'
	elif A == D:                                        # 3 из 6
		if ax == bx:
			if cx == ax:
				figure = 'Треугольник'
			elif cx != ax:
				figure = 'Отрезок'
		elif ax != bx:
			Kkoefab = (ay - by)/(ax - bx)
			Bkoefab = ay - Kkoefab * ax
			if cy != Kkoefab * cx + Bkoefab:
				figure = 'Треугольник'
			elif cy == Kkoefab * cx + Bkoefab:
				figure = 'Отрезок'
	elif B == C:                                        # 4 из 6
		if ax == bx:
			if dx != ax:
				figure = 'Треугольник'
			elif dx == ax:
				figure = 'Отрезок'
		elif ax != bx:
			Kkoefab = (ay - by)/(ax - bx)
			Bkoefab = ay - Kkoefab * ax
			if dy != Kkoefab * dx + Bkoefab:
				figure = 'Треугольник'
			elif dy == Kkoefab * dx + Bkoefab:
				figure = 'Отрезок'
	elif B == D:                                        # 5 из 6
		if ax == bx:
			if cx == ax:
				figure = 'Треугольник'
			elif cx != ax:
				figure = 'Отрезок'
		elif ax != bx:
			Kkoefab = (ay - by)/(ax - bx)
			Bkoefab = ay - Kkoefab * ax
			if cy != Kkoefab * cx + Bkoefab:
				figure = 'Треугольник'
			elif cy == Kkoefab * cx + Bkoefab:
				figure = 'Отрезок'
	elif C == D:                                       # 6 из 6
		if ax == bx:
			if dx != ax:
				figure = 'Треугольник'
			elif dx == ax:
				figure = 'Отрезок'
		elif ax != bx:
			Kkoefab = (ay - by)/(ax - bx)
			Bkoefab = ay - Kkoefab * ax
			if dy != Kkoefab * dx + Bkoefab:
				figure = 'Треугольник'
			elif dy == Kkoefab * dx + Bkoefab:
				figure = 'Отрезок'
elif (A == B and B == C and C != D) or (A == B and B == D and A != C) or (A == C and c == D and A != B) or (A != B and B == C and C == D):   # Если 3 точки совпадают
	figure == 'Отрезок'
elif (A == B and C == D and A != C) or (A == C and B == D and A != B) or (A == D and B == C and A != B):     # Если 2 пары совпадающих точек
	figure = 'Отрезок'
elif A == B and B == C and C == D:
	figure = 'Точка'

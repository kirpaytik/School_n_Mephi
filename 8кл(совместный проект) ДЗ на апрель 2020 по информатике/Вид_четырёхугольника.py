A = str(input())
B = str(input())
C = str(input())
D = str(input())

ax = int( A[0 : A.find(' ')] )
bx = int( B[0 : B.find(' ')] )
cx = int( C[0 : C.find(' ')] )
dx = int( D[0 : D.find(' ')] )

ay = int( A[A.find(' ')+1 : ] )
by = int( B[B.find(' ')+1 : ] )
cy = int( C[C.find(' ')+1 : ] )
dy = int( D[D.find(' ')+1 : ] )

def yravneniepryamoi(x1,x2,y1,y2,z):
    if x1==x2:
        z = 'x = ' + str(x1)
    elif y1==0 and y2==0:
        z = 'y = 0'
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
            z = 'y = ' + b
        elif k!=0:
            if b>0:
                b = str(b)
                b = '+ ' + b
            elif b==0:
                b = ''
            elif b<0:
                b = str(b)
                b = '- ' + b[1:]
            z = 'y = ' + k + 'x ' + b
    return z

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

def rasstoyanie(vx,wx,vy,wy,gip):
    kat1 = abs(wx-vx)
    kat2 = abs(wy-vy)
    gip = (kat1**2 + kat2**2)**0.5
    return gip
AB = 0
BC = 0
CD = 0
AD = 0
AB = rasstoyanie(ax, bx, ay, by, AB)
BC = rasstoyanie(bx, cx, by, cy, BC)
CD = rasstoyanie(cx, dx, cy, dy, CD)
AD = rasstoyanie(ax, dx, ay, dy, AD)
AC = rasstoyanie(ax, cx, ay, cy, AC)
if figure = 'Четырёхугольник':
	zab = 0
	zcd = 0
	zad = 0
	zbc = 0
	zab = yravneniepryamoi(ax, bx, ay, by, zab)
	zcd = yravneniepryamoi(cx, dx, cy, dy, zcd)
	zad = yravneniepryamoi(ax, dx, ay, dy, zad)
	zbc = yravneniepryamoi(bx, cx, by, cy, zbc)
	parallABcd = 0
	parallADbc = 0
	parallABcd = parallelnost(zab, zcd, parallABcd)
	parallADbc = parallelnost(zad, zbc, parallADbc)
	if parallABcd = 'Параллельны' and parallADbc = 'Параллельны':
		figure = 'Параллелограмм'
	elif (parallABcd == 'Не параллельны' and parallADbc == 'Параллельны') or (parallABcd == 'Параллельны' and parallADbc == 'Не параллельны'):
		figure = 'Трапеция'
	elif parallABcd == 'Не параллельны' and parallADbc == 'Не параллельны':
		figure == 'Простой четырёхугольник'
if figure == 'Параллелограмм':
	csimm = 
	if (AC**2 == AB**2 + BC**2) and (AB == BC):
		figure = 'Квадрат'
	elif (AC**2 != AB**2 + BC**2) and (AB == BC):
		figure = 'Ромб'
	elif (AC**2 == AB**2 + BC**2) and (AB != BC):
		figure = 'Прямоугольник'
	elif (AC**2 != AB**2 + BC**2) and (AB != BC):
		figure = 'Параллелограмм'
elif figure == 'Трапеция':
	if parallABcd == 'Параллельны':
		if AD == BC:
			figure = 'Равнобедренная трапеция'
		elif (AC**2 == AB**2 + BC**2) or (AC**2 == AD**2 + CD**2):
			figure = 'Прямоугольная трапеция'
	elif parallADbc == 'Параллельны':
		if AB == CD:
			figure = 'Равнобедренная трапеция'
		elif (AC**2 == AB**2 + BC**2) or (AC**2 == AD**2 + CD**2):
			figure = 'Прямоугольная трапеция'
elif figure == 'Простой четырёхугольник':
	if ax == cx:
		if (bx>ax and dx<ax) or (bx<ax and dx>ax):
			vip13 = 'Выпуклый'
		elif (bx>ax and dx>ax) or (bx<ax and dx<ax):
			vip13 = 'Не выпуклый'
	elif ay == cy:
		if (by>ay and dy<ay) or (by<ay and dy>ay):
			vip13 = 'Выпуклый'
		elif (by>ay and dy>ay) or (by<ay and dy<ay):
			vip13 = 'Не выпуклый'
	elif (ax != cx) and (ay != cy):
		Kkoefac = (ay - cy)/(ax - cx)
		Bkoefac = ay - Kkoefac * ax
		if (by > (Kkoefac * bx + Bkoefac) and dy < (Kkoefac * dx + Bkoefac)) or (by < (Kkoefac * bx + Bkoefac) and dy > (Kkoefac * dx + Bkoefac)):
			vip13 = 'Выпуклый'
		elif (by > (Kkoefac * bx + Bkoefac) and dy > (Kkoefac * dx + Bkoefac)) or (by < (Kkoefac * bx + Bkoefac) and dy < (Kkoefac * dx + Bkoefac)):
			vip13 = 'Не выпуклый'

	if bx == dx:
		if (ax>bx and cx<bx) or (ax<bx and cx>bx):
			vip24 = 'Выпуклый'
		elif (ax>bx and cx>bx) or (ax<bx and cx<bx):
			vip24 = 'Не выпуклый'
	elif by == dy:
		if (ay>by and cy<by) or (ay<by and cy>by):
			vip24 = 'Выпуклый'
		elif (ay>by and cy>by) or (ay<by and cy<by):
			vip24 = 'Не выпуклый'
	elif (bx != dx) and (by != dy):
		Kkoefbd = (by - dy)/(bx - dx)
		Bkoefbd = by - Kkoefbd * bx
		if (ay > (Kkoefbd * ax + Bkoefbd) and cy < (Kkoefbd * cx + Bkoefbd)) or (ay < (Kkoefbd * ax + Bkoefbd) and cy > (Kkoefbd * cx + Bkoefbd)):
			vip24 = 'Выпуклый'
		elif (ay > (Kkoefbd * ax + Bkoefbd) and cy > (Kkoefbd * cx + Bkoefbd)) or (ay < (Kkoefbd * ax + Bkoefbd) and cy < (Kkoefbd * cx + Bkoefbd)):
			vip24 = 'Не выпуклый'
	if vip13 
	if (AB == BC and AD == CD) or (AB == AD and BC == CD):
		

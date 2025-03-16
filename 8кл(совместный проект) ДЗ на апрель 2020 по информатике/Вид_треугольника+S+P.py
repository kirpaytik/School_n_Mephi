A= str(input())
B= str(input())
C= str(input())
D= str(input())

ax = int( A[0 : A.find(' ')] )
bx = int( B[0 : B.find(' ')] )
cx = int( C[0 : C.find(' ')] )
dx = int( D[0 : D.find(' ')] )

ay = int( A[A.find(' ')+1 : ] )
by = int( B[B.find(' ')+1 : ] )
cy = int( C[C.find(' ')+1 : ] )
dy = int( D[D.find(' ')+1 : ] )

def rasstoyanie(x1,x2,y1,y2,gip):
    kat1 = abs(x2-x1)
    kat2 = abs(y2-y1)
    gip = (kat1**2 + kat2**2)**0.5
    return gip
   
AB = rasstoyanie(ax, bx, ay, by, AB)
BC = rasstoyanie(bx, cx, by, cy, BC)
CD = rasstoyanie(cx, dx, cy, dy, CD)
AD = rasstoyanie(ax, dx, ay, dy, AD)

if figure = 'Треугольник':
	vpisokr = 'Можно вписать окружность'
	opisokr = 'Можно описать окружность'
	if A==B or B==C or C==D or A==D:                            # Если 2 точки совпадают
		if A==D or B==D or C==D:
			treygolnik = 'ABC'
		elif A==C or B==C:
			treygolnik = 'ABD'
		elif A==B:
			treygolnik = 'ACD'
	elif A!=B and A!=C and A!=D and B!=C and B!=D and C!=D:     # Если 1 точка лежит на стороне треугльника
		if ax == bx:
			if (dx == ax) or (dy == Kkoefac * dx + Bkoefac) or (dy == Kkoefbc * dx + Bkoefbc):
				if dx == ax:
					if AB>AD and AB>BD:
						treygolnik = 'ABC'
					elif AD>AB and AD>BD:
						treygolnik = 'ACD'
					elif BD>AB and BD>AD:
						treygolnik = 'BCD'
				elif dy == Kkoefac * dx + Bkoefac:
					if AC>AD and AC>CD:
						treygolnik = 'ABC'
					elif AD>AC and AD>CD:
						treygolnik = 'ABD'
					elif CD>AC and CD>AD:
						treygolnik = 'BCD'
				elif dy == Kkoefbc * dx + Bkoefbc:
					if BC>BD and BC>CD:
						treygolnik = 'ABC'
					elif BD>BC and BD>CD:
						treygolnik = 'ABD'
					elif CD>BC and CD>BD:
						treygolnik = 'ACD'
			elif cx == ax:
				if AB>AC and AB>BC:
					treygolnik = 'ABD'
				elif AC>AB and AC>BC:
					treygolnik = 'ACD'
				elif BC>AB and BC>AC:
					treygolnik = 'BCD'
		elif ax == cx:
			if (dy == Kkoefab * dx + Bkoefab) or (dx == ax) or (dy == Kkoefbc * dx + Bkoefbc):
				if dy == Kkoefab * dx + Bkoefab:
					if AB>AD and AB>BD:
						treygolnik = 'ABC'
					elif AD>AB and AD>BD:
						treygolnik = 'ACD'
					elif BD>AB and BD>AD:
						treygolnik = 'BCD'
				elif dx == ax:
					if AC>AD and AC>CD:
						treygolnik = 'ABC'
					elif AD>AC and AD>CD:
						treygolnik = 'ABD'
					elif CD>AC and CD>AD:
						treygolnik = 'BCD'
				elif dy == Kkoefbc * dx + Bkoefbc:
					if BC>BD and BC>CD:
						treygolnik = 'ABC'
					elif BD>BC and BD>CD:
						treygolnik = 'ABD'
					elif CD>BC and CD>BD:
						treygolnik = 'ACD'
			elif bx == ax:
				if AB>AC and AB>BC:
					treygolnik = 'ABD'
				elif AC>AB and AC>BC:
					treygolnik = 'ACD'
				elif BC>AB and BC>AC:
					treygolnik = 'BCD'
		elif bx == cx:
			if (dy == Kkoefab * dx + Bkoefab) or (dy == Kkoefac * dx + Bkoefac) or (dx == bx):
				if dy == Kkoefab * dx + Bkoefab:
					if AB>AD and AB>BD:
						treygolnik = 'ABC'
					elif AD>AB and AD>BD:
						treygolnik = 'ACD'
					elif BD>AB and BD>AD:
						treygolnik = 'BCD'
				elif dy == Kkoefac * dx + Bkoefac:
					if AC>AD and AC>CD:
						treygolnik = 'ABC'
					elif AD>AC and AD>CD:
						treygolnik = 'ABD'
					elif CD>AC and CD>AD:
						treygolnik = 'BCD'
				elif dx == bx:
					if BC>BD and BC>CD:
						treygolnik = 'ABC'
					elif BD>BC and BD>CD:
						treygolnik = 'ABD'
					elif CD>BC and CD>BD:
						treygolnik = 'ACD'
			elif ax == bx:
				if AB>AC and AB>BC:
					treygolnik = 'ABD'
				elif AC>AB and AC>BC:
					treygolnik = 'ACD'
				elif BC>AB and BC>AC:
					treygolnik = 'BCD'
		elif ax!=bx  and  ax!=cx  and  bx!=cx:
			if (dy == Kkoefab * dx + Bkoefab) or (dy == Kkoefac * dx + Bkoefac) or (dy == Kkoefbc * dx + Bkoefbc):
				if dy == Kkoefab * dx + Bkoefab:
					if AB>AD and AB>BD:
						treygolnik = 'ABC'
					elif AD>AB and AD>BD:
						treygolnik = 'ACD'
					elif BD>AB and BD>AD:
						treygolnik = 'BCD'
				elif dy == Kkoefac * dx + Bkoefac:
					if AC>AD and AC>CD:
						treygolnik = 'ABC'
					elif AD>AC and AD>CD:
						treygolnik = 'ABD'
					elif CD>AC and CD>AD:
						treygolnik = 'BCD'
				elif dy == Kkoefbc * dx + Bkoefbc:
					if BC>BD and BC>CD:
						treygolnik = 'ABC'
					elif BD>BC and BD>CD:
						treygolnik = 'ABD'
					elif CD>BC and CD>BD:
						treygolnik = 'ACD'
			elif cy == Kkoefab * cx + Bkoefab:
				if AB>AC and AB>BC:
					treygolnik = 'ABD'
				elif AC>AB and AC>BC:
					treygolnik = 'ACD'
				elif BC>AB and BC>AC:
					treygolnik = 'BCD'

	if treygolnik = 'ABC':                                      # Какой трегуольник 1 из 4
		if AB==AC or AB==BC or AC==BC:                          # Вид по сторонам
			vidtr = 'Равнобедренный '
		elif AB==AC and AB==BC:
			vidtr = 'Равносторонний '
		elif AB!=AC and AB!=BC and AC!=BC:
			vidtr = 'Разносторонний '

		if AB>AC and AB>BC:                                     # Вид по углам
			if AB**2 > AC**2 + BC**2:
				vidtr += 'тупоугольный'
			elif AB**2 == AC**2 + BC**2:
				vidtr += 'прямоугольный'
			elif AB**2 < AC**2 + BC**2:
				vidtr += 'остроугльный'
		elif AC>AB and AC>BC:
			if AC**2 > AB**2 + BC**2:
				vidtr += 'тупоугольный'
			elif AC**2 == AB**2 + BC**2:
				vidtr += 'прямоугольный'
			elif AC**2 < AB**2 + BC**2:
				vidtr += 'остроугльный'
		elif BC>AB and BC>AC:
			if BC**2 > AB**2 + AC**2:
				vidtr += 'тупоугольный'
			elif BC**2 == AB**2 + AC**2:
				vidtr += 'прямоугольный'
			elif BC**2 < AB**2 + AC**2:
				vidtr += 'остроугльный'

		P = AB + AC + BC
		p = P/2
		S = (p * (p-AB) * (p-ac) * (p-BC))**0.5
	elif treygolnik = 'ABD':                                    # Какой трегуольник 2 из 4
		if AB==AD or AB==BD or AD==BD:                          # Вид по сторонам
			vidtr = 'Равнобедренный '
		elif AB==AD and AB==BD:
			vidtr = 'Равносторонний '
		elif AB!=AD and AB!=BD and AD!=BD:
			vidtr = 'Разносторонний '

		if AB>AD and AB>BD:                                     # Вид по углам
			if AB**2 > AD**2 + BD**2:
				vidtr += 'тупоугольный'
			elif AB**2 == AD**2 + BD**2:
				vidtr += 'прямоугольный'
			elif AB**2 < AD**2 + BD**2:
				vidtr += 'остроугльный'
		elif AD>AB and AD>BD:
			if AD**2 > AB**2 + BD**2:
				vidtr += 'тупоугольный'
			elif AD**2 == AB**2 + BD**2:
				vidtr += 'прямоугольный'
			elif AD**2 < AB**2 + BD**2:
				vidtr += 'остроугльный'
		elif BD>AB and BD>AD:
			if BD**2 > AB**2 + AD**2:
				vidtr += 'тупоугольный'
			elif BD**2 == AB**2 + AD**2:
				vidtr += 'прямоугольный'
			elif BD**2 < AB**2 + AD**2:
				vidtr += 'остроугльный'
		
		P = AB + AD + BD
		p = P/2
		S = (p * (p-AB) * (p-AD) * (p-BD))**0.5
	elif treygolnik = 'ACD':                                    # Какой трегуольник 3 из 4
		if AC==AD or AC==CD or AD==CD:                          # Вид по сторонам
			vidtr = 'Равнобедренный '
		elif AC==AD and AC==CD:
			vidtr = 'Равносторонний '
		elif AC!=AD and AC!=CD and AD!=CD:
			vidtr = 'Разносторонний '

		if AC>AD and AC>CD:                                     # Вид по углам
			if AC**2 > AD**2 + CD**2:
				vidtr += 'тупоугольный'
			elif AC**2 == AD**2 + CD**2:
				vidtr += 'прямоугольный'
			elif AC**2 < AD**2 + CD**2:
				vidtr += 'остроугльный'
		elif AD>AC and AD>CD:
			if AD**2 > AC**2 + CD**2:
				vidtr += 'тупоугольный'
			elif AD**2 == AC**2 + CD**2:
				vidtr += 'прямоугольный'
			elif AD**2 < AC**2 + CD**2:
				vidtr += 'остроугльный'
		elif CD>AC and CD>AD:
			if CD**2 > AC**2 + AD**2:
				vidtr += 'тупоугольный'
			elif CD**2 == AC**2 + AD**2:
				vidtr += 'прямоугольный'
			elif CD**2 > AC**2 + AD**2:
				vidtr += 'остроугльный'

		P = AC + AD + CD
		p = P/2
		S = (p * (p-AC) * (p-AD) * (p-CD))**0.5
	elif treygolnik = 'BCD':
		if BC==BD or BC==CD or BD==CD:
			vidtr = 'Равнобедренный '
		elif BC==BD and BC==CD:
			vidtr = 'Равносторонний '
		elif BC!=BD or BC!=CD or BD!=CD:
			vidtr = 'Разносторонний '

		if BC>BD and BC>CD:
			if BC**2 > BD**2 + CD**2:
				vidtr += 'тупоугольный'
			elif BC**2 == BD**2 + CD**2:
				vidtr += 'прямоугольний'
			elif BC**2 < BD**2 + CD**2:
				vidtr += 'остроугольный'
		elif BD>BC and BD>CD:
			if BD**2 > BC**2 + CD**2:
				vidtr += 'тупоугольный'
			elif BD**2 == BC**2 + CD**2:
				vidtr += 'прямоугольний'
			elif BD**2 < BC**2 + CD**2:
				vidtr += 'остроугольный'
		elif CD>BC and CD>BD:
			if CD**2 > BC**2 + BD**2:
				vidtr += 'тупоугольный'
			elif CD**2 == BC**2 + BD**2:
				vidtr += 'прямоугольний'
			elif CD**2 < BC**2 + BD**2:
				vidtr += 'остроугольный'

		P = BC + BD + CD
		p = P/2
		S = (p * (p-BC) * (p-BD) * (p-CD))**0.5

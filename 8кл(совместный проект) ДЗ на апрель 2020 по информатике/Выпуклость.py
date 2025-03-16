def vipyklost(t1x, t2x, t3x, t4x, t1y, t2y, t3y, t4y):
	if t1x == t3x:
		if (t2x>t1x and t4x>t1x) or (t2x<t1x and t4x<t1x):
			vip13 = 'Выпуклый'
		elif (t2x>t1x and t4x<t1x) or (t2x<t1x and t4x>t1x):
			vip13 = 'Не выпуклый'
	elif t1y == t3y:
		if (t2y>t1y and t4y>t1y) or (t2y<t1y and t4y<t1y):
			vip13 = 'Выпуклый'
		elif (t2y>t1y and t4y<t1y) or (t2y<t1y and t4y>t1y):
			vip13 = 'Не выпуклый'
	elif (t1x != t3x) and (t1y != t3y):
		Kkoef13 = (t1y - t3y)/(t1x - t3x)
		Bkoef13 = t1y - Kkoef13 * t1x
		if (t2y > (Kkoef13 * t2x + Bkoef13) and t4y > (Kkoef13 * t4x + Bkoef13)) or (t2y < (Kkoef13 * t2x + Bkoef13) and t4y < (Kkoef13 * t4x + Bkoef13)):
			vip13 = 'Выпуклый'
		elif (t2y > (Kkoef13 * t2x + Bkoef13) and t4y < (Kkoef13 * t4x + Bkoef13)) or (t2y < (Kkoef13 * t2x + Bkoef13) and t4y > (Kkoef13 * t4x + Bkoef13)):
			vip13 = 'Не выпуклый'

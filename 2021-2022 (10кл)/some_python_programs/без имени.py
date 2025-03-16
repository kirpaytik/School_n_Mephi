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
		

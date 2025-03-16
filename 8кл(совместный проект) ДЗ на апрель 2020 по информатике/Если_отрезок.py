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

if figure == 'Отрезок':
	dlina = AD
	yravnenie = yravneniepryamoi(ax, dx, ay, dy, yravnenie)

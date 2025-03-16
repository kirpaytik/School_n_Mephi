def yravneniepryamoi(x1,x2,y1,y2,z):
    if x1==x2:
        z = 'x=' + x1
    elif y1==y2:
        z = 'y=' + y1
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
        
		if b>0:
			b = str(b)
			b = '+' + b
		elif b==0:
			b = ''
		elif b<0:
			b = str(b)
		z = 'y=' + k + 'x' + b
    return z

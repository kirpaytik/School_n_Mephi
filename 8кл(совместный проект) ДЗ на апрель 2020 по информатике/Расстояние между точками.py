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

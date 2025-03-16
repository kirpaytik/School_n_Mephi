def chetverti(p, px, py):
    if py>0:
        if px>0:
            p = '1 четверть'
        elif px<0:
            p = '2 четверть'
        elif px==0:
            p = '1-2 четверть'
    elif py<0:
        if px<0:
            p = '3 четверть'
        elif px>0:
            p = '4 четверть'
        elif px==0:
            p = '3-4 четверть'
    elif py==0:
        if px<0:
            p = '2-3 четверть'
        elif px>0:
            p = '1-4 четверть'
        elif px==0:
            p = '1234 четверть'
    return p
a = 0
b = 0
c = 0
d = 0
a = chetverti(a, ax, ay)
b = chetverti(b, bx, by)
c = chetverti(c, cx, cy)
d = chetverti(d, dx, dy)

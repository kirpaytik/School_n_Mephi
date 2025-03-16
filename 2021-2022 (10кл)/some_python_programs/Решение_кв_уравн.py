print("Введите последовательно коэффициенты a,b,c уравнения ax^2 + bx + c = 0, разделяя их только пробелами.")
koef = input().split(" ")
while len(koef)>0:
    if koef[0]=="":
        koef.pop(0)
    else:
        break
while len(koef)>1:
    if koef[1]=="":
        koef.pop(1)
    else:
        break
while len(koef)>2:
    if koef[2]=="":
        koef.pop(2)
    else:
        break
while len(koef)>3:
    if koef[3]=="":
        koef.pop(3)
    else:
        break
if len(koef)<3:
    raise SystemExit("Введено меньше 3х коэффициентов")
elif len(koef)>3:
    raise SystemExit("Введено больше 3х коэффициентов")
koef = [float(i) for i in koef]
a = koef[0]
a = int(a) if a == int(a) else a
b = koef[1]
b = int(b) if b == int(b) else b
c = koef[2]
c = int(c) if c == int(c) else c
if a<0:
    print("Для удобства решения советуем умножать обе части уравнения на -1, если коэффициент a<0. Решения изначального и полученного уравнений будут совпадать.")
    a = -a
    b = -b
    c = -c
    print("Умножив обе части уравнения на -1, получим новые коэффициенты:", a, b, c, "\n")
k = 2
delKoef = []
ak = a
bk = b
ck = c
while k <= min(a,b,c)/2:
    if ak%k==0 and bk%k==0 and ck%k==0:
        delKoef.append(k)
        ak = ak/k
        bk = bk/k
        ck = ck/k
    else:
        k+=1
if len(delKoef) > 0:
    print("Можно заметить, что все коэффициенты уравнения имеют общий делитель, больший 1.")
    print("Для удобства решения советуем разделить обе части уравнения на этот делитель, чтобы работа велась с мЕньшими числами, и вычисления были проще.")
    a = a//delKoef[0]
    b = b//delKoef[0]
    c = c//delKoef[0]
    print("Можем поделить на ", delKoef[0], ". Новые коэффициенты: ", a, ", ", b, ", ",c, sep="")
    delKoef.pop(0)
    while len(delKoef) > 0:
        a = int(a / delKoef[0])
        b = int(b / delKoef[0])
        c = int(c / delKoef[0])
        print("Можем ещё поделить на ", delKoef[0], ". Новые коэффициенты: ", a, ", ", b, ", ",c, sep="")
        delKoef.pop(0)
aa = "" if a==1 else a
znb = "+" if b>0 else "-"
if abs(b)==1:
    bb = ""
else:
    bb = b
znc = "+" if c>0 else "-"
if a != 0:

    if b==0:

        if c==0:
            print("Уравнение: ", aa, "x^2 = 0", sep="")
            print("Решение:")
            print(aa, "x^2 = 0", sep="")
            print("x^2 = 0")
            print("x = 0")
            otvet = "x = 0"

        else: # if c!=0
            print("Уравнение: ", aa, "x^2 ", znc, " ", abs(c), " = 0", sep="")
            print("Решение:")
            print(aa, "x^2 ", znc, " ", abs(c), " = 0", sep="")
            print(aa, "x^2 = ", -c, sep="")

            if c<0: # if a*c<0 (x^2 = >0)
                x = -c
                if a!=1:
                    x = x/a
                    x = int(x) if x == int(x) else x
                    drobcherta = max(len(str(a)), len(str(-c)) ) + 4
                    print(" "*6, " "*((drobcherta - len(str(-c)) )//2), -c, sep="")
                    print("x^2 = ", "-"*drobcherta, " = ", x, sep="")
                    print(" "*6, " "*((drobcherta - len(str(a)) )//2), a, sep="")
                x05 = x**0.5
                x05 = int(x05) if x05 == int(x05) else x05
                print("x = +-sqrt(", x, ") = +-", x05, sep="")
                otvet = "x1 = " + str(x05) + ", x2 = -" + str(x05)

            else: # elif c>0 (a*c>0) (x^2 = <0) (будут комплЕксные корни)
                print("Действительных корней нет.")
                x = -c
                if a!=1:
                    x = x/a
                    x = int(x) if x == int(x) else x
                    drobcherta = max(len(str(a)), len(str(c))) + 4
                    print(" " * 6, " " * ((drobcherta - len(str(-c))) // 2), -c, sep="")
                    print("x^2 = ", "-" * drobcherta, " = ", x, sep="")
                    print(" " * 6, " " * ((drobcherta - len(str(a))) // 2), a, sep="")
                x05 = (-x)**0.5
                x05 = int(x05) if x05 == int(x05) else x05
                if x05==1:
                    print("x = +-sqrt(", x, ") = +-j", sep="")
                    otvet = "x1 = j, x2 = -j"
                else:
                    print("x = +-sqrt(", x, ") = +-", x05, "*j", sep="")
                    otvet = "x1 = " + str(x05) + "*j, x2 = -" + str(x05) + "*j"

    else: # if b!=0

        if c==0:
            print("Уравнение: ", aa, "x^2 ", znb, " ", ("" if b==1 else abs(bb)), "x = 0", sep="")
            print("Решение:")
            print(aa, "x^2 ", znb, " ", ("" if b==1 else abs(bb)), "x = 0", sep="")
            print("x*(", aa, "x ", znb, " ", (1 if b==1 else abs(bb)), ") ", "= 0", sep="")
            print("x = 0 или ", aa, "x ", znb, " ", (1 if b==1 else abs(bb)), " = 0", sep="")
            print(" "*10, aa, "x = ", -b, sep="")
            x2 = -b
            if a!=1:
                x2 = x2/a
                drobcherta = max(len(str(abs(b))), len(str(a)) ) + 4
                x2 = int(x2) if x2 == int(x2) else x2
                print(" "*10, " "*4, " "*((drobcherta - len(str(-b)) )//2), -b, sep="")
                print(" "*10, "x = ", "-"*drobcherta, " = ", x2, sep="")
                print(" "*10, " "*4, " "*((drobcherta - len(str(a)) )//2), a, sep="")
            otvet = "x1 = 0, x2 = " + str(x2)

        else: # if c!=0
            print("Уравнение: ", aa, "x^2 ", znb, " ", ("" if bb=="" else abs(bb)), "x " , znc, " ", abs(c), " = 0", sep="")
            D = b * b - 4 * a * c

            if D==0:
                print('Решение с применением некоторого "творчества":')
                print("    Можно заметить, что коэффициент b равен удвоенному произведению корней из коэффициентов a и c (или же просто D=0).")
                print("    То бишь можно представить уравнение в виде y^2 + 2yz + z^2, где y=sqrt(a)*x, z = sqrt(c).")
                print("    Нетрудно догадаться, что это полный квадрат. Свернём его и довольно быстро получим решение:")
                if aa == "":
                    aa05_ = ""
                else:
                    aa05 = aa ** 0.5
                    aa05 = int(aa05) if aa05 == int(aa05) else aa05
                    aa05_ = str(aa05) + "*"
                c05 = c**0.5
                c05 = int(c05) if c05 == int(c05) else c05
                print(" "*4, aa, "x^2 ", znb, " ", abs(bb), "x ", znc, " ", abs(c), " = (", aa05_, "x ", znb, " ", c05, ")^2 = 0", sep="")
                print(" "*4, aa05_, "x ", znb, " ", c05, " = 0", sep="")
                _znb = "-" if znb == "+" else ""
                print(" "*4, "x = ", _znb, c05, sep="")
                print()
                print("Дальше решение по уже известным алгоритмам:")

            if abs(a+c)==abs(b): # Связь коэффициентов (по теореме Виета)
                if a+b+c==0:
                    print("Можно заметить, что сумма коэффициентов равна 0. По теореме Виета это значит, что один из корней равен 1")
                    x1 = 1
                else: # if a-b+c==0
                    print("Можно заметить, что сумма коэффициентов a и c равна коэффициенту b. По теореме Виета это значит, что один из корней равен -1")
                    x1 = -1
                print("Также по теореме Виета произведение корней равно c/a. Зная, что первый корень равен ", x1, ", мы находим второй корень:", sep="")
                print("x1*x2 = c/a")
                ca = c/a
                ca = int(ca) if ca == int(ca) else ca
                print(x1, "*x2 = ", ca, sep="")
                x2 = ca if x1==1 else -ca
                print("x2 =", x2)
            else: # Теорема Виета
                if b==int(b) and (c*a)%1==0:
                    q = c*a
                    p = b
                    delitQ = [1]
                    n = 2
                    while n<=abs(q)**0.5:
                        if q%n==0:
                            delitQ.append(n)
                        n+=1
                    for i in delitQ:
                        if abs(i + q/i) == abs(b):
                            if i + q/i == b:
                                x1v = -i
                                x2v = -int(q/i)
                            else: # if i + q/i == -b
                                x1v = i
                                x2v = int(q/i)
                            x1v = x1v/a
                            x1v = int(x1v) if x1v == int(x1v) else x1v
                            x2v = x2v/a
                            x2v = int(x2v) if x2v == int(x2v) else x2v
                            print("По теореме Виета:")
                            print("{ x1 + x2 = -b/a = -(", b, "/", a, ") = ", -p, sep="")
                            print("{ x1 * x2 = c/a = ", c, "/", a, " = ", q, sep="")
                            print("Можно заметить, что числа ", x1v, " и ", x2v, " удовлетворяют условиям системы.", sep="")
                            print("Тогда по теореме, обратной теореме Пифагора, эти числа являются корнями уравнения x^2 ", znb, " ", p, " ", znc, " ", q, " = 0.", sep="")
                            print("А корни этого уравнения совпадают с корнями нашего уравнения, т.к. это и есть наше уравнение в приведённом виде. (домножив обе части этого уравнения на коэффициент a нашего уравнения мы получим его же)")
                            print("x1 = ", x1v, ", x2 = ", x2v, sep="")
                            print()
                            break
                elif b%1!=0:
                    bint = 

            znac = "+" if a * c < 0 else "-"
            print("D = b^2 - 4*a*c = ", b, "^2 - 4*", a, "*", c, " = ", b * b, " ", znac, " ", abs(4 * a * c),
                  " = ", D, sep="")

            if D==0:


                x = -b / (2 * a)
                x = int(x) if x == int(x) else x
                print("Решение через дискриминант:")
                print("D=0 => Есть 2 одинаковых действительных корня.")
                drobcherta = max(len(str(a)) + 2, len(str(abs(b))) + 10) + 4
                print(" "*4, " "*((drobcherta - len(str(b)) - 10 - (2 if b>0 else 0) + 1)//2), -b, " +- sqrt(0)", sep="")
                print("x = ", "-"*drobcherta, " = ", x, sep="")
                print(" "*4, " "*((drobcherta - len(str(a)) - 2) // 2), "2*", a, sep="")
                otvet = "x1 = " + str(x) + ", x2 = " + str(x)

            elif D>0:
                print("Решение через дискриминант:")
                print("D>0 => Есть 2 различных действительных корня.")
                x1 = (-b + D**0.5)/(2*a)
                x2 = (-b - D**0.5)/(2*a)
                x1 = int(x1) if x1 == int(x1) else x1
                x2 = int(x2) if x2 == int(x2) else x2
                drobcherta = max(len(str(a)) + 2, len(str(-b)) + 9 + len(str(D)) ) + 4
                print(" "*5, " "*((drobcherta - len(str(b)) - 9 - len(str(D)) + (2 if b<0 else 0) )//2), -b, " + sqrt(", D, ")", sep="")
                print("x1 = ", "-"*drobcherta, " = ", x1, sep="")
                print(" "*5, " "*((drobcherta - len(str(a)) - 2) // 2), "2*", a, sep="")

                print(" "*5, " "*((drobcherta - len(str(b)) - 9 - len(str(D)) + (2 if b<0 else 0) )//2), -b, " - sqrt(", D, ")", sep="")
                print("x2 = ", "-"*drobcherta, " = ", x2, sep="")
                print(" "*5, " "*((drobcherta - len(str(a)) - 2) // 2), "2*", a, sep="")
                otvet = "x1 = " + str(x1) + ", x2 = " + str(x2)

            else: # elif D<0
                print("Решение через дискриминант:")
                print("D<0 => Действительных корней нет. Корнями будут являться два комплексно-сопряжённых числа.")
                D05 = (-D)**0.5
                xa = -b/(2*a)
                xa = int(xa) if xa == int(xa) else xa
                xj = D05/(2*a)
                xj = int(xj) if xj == int(xj) else xj
                xj = str(xj) + "*j"
                drobcherta = max(len(str(a)) + 2, len(str(-b)) + 10 + len(str(D))) + 4
                probelChislX = (drobcherta - len(str(b)) - 10 - len(str(D)) + (2 if b < 0 else 0)) // 2
                probelZnamX = (drobcherta - len(str(a)) - 2) // 2

                drobchertaXa = max(len(str(2*a)), len(str(abs(b))) ) + 2
                probelChislXa = (drobchertaXa - len(str(-b)) ) // 2
                probelZnamXa = (drobchertaXa - len(str(2*a)) ) // 2

                drobchertaXj = max(len(str(2*a)), len(str(D05)) + 2) + 2
                probelChislXj = (drobchertaXj - len(str(D05)) - 2) // 2
                probelZnamXj = (drobchertaXj - len(str(2*a)) ) // 2

                print(" "*4, " "*probelChislX, -b, " +- sqrt(", D, ")", " "*probelChislX, " "*3, " "*probelChislXa, -b, " "*(probelChislXa + (1 if b>0 else 0)), " "*4, " "*probelChislXj, D05, "*j", sep="")
                print("x = ", "-"*drobcherta, " = ", "-"*drobchertaXa, " +- ", "-"*drobchertaXj, " = ", xa, " +- ", xj, sep="")
                print(" "*4, " "*probelZnamX, "2*", a, " "*(probelZnamX + (1 if (drobcherta - len(str(a)) )%2==1 else 0)), " "*3, " "*probelZnamXa, 2*a, " "*probelZnamXa, " "*4, " "*probelZnamXj, 2*a, sep="")
                otvet = "x1 = " + str(xa) + " + " + str(xj) + ", x2 = " + str(xa) + " - " + str(xj)

else: # if a==0
    print("Старший коэффициент (a) равен нулю, а значит, уравнение с введёнными коэффициентами не является квадратным, то бишь является линейным")

    if b==0:

        if c==0:
            print("Уравнение: 0 = 0")
            print("Решение:")
            print("0 = 0 - верное равенство, независящее от x")
            otvet = "x - любое число"

        else: # if c!=0
            print("Уравнение:", c, "= 0")
            print("Решение:")
            print(c, "= 0 - неверное равенство, независящее от x")
            otvet = "решений нет"

    else: # if b!=0

        if c==0:
            print("Уравнение: ", bb, "x = 0", sep="")
            print("Решение:")
            print(bb, "x = 0", sep="")
            print("x = 0")
            otvet = "x = 0"

        else: # if c!=0
            print("Уравнение: ", bb, "x ", znc, " ", abs(c), " = 0", sep="")
            print("Решение:")
            print(bb, "x ", znc, " ", abs(c), " = 0", sep="")
            print(bb, "x = ", -c, sep="")
            if b!=1:
                x = -c/b
                x = int(x) if x == int(x) else x
                drobcherta = max(len(str(abs(b))), len(str(abs(c))) ) + 4
                print(" " * (4 + (drobcherta - len(str(-c))) // 2), -c, sep="")
                print("x = ", "-"*drobcherta, " = ", x, sep="")
                print(" " * (4 + (drobcherta - len(str(b))) // 2), b, sep="")
                otvet = "x = " + str(x)
            else:
                otvet = "x = " + str(-c)
print()
print("Ответ: ", otvet)

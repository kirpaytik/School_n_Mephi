print("Введите количество аргументов функции")
kolarg = int(input())
print("Введите через пробел номера строк таблицы истинности, на которых функция принимает значение true")
print("(примечания: первая строка имеет номер 0;   ваша функция имеет " + str(2**kolarg) + " строк, так что каждое введённое в строке число не может превышать " + str(2**kolarg-1))
numtrue = str(input()).split(" ")
for i in numtrue:
	if(int(i)>2**kolarg-1):
		raise SystemExit("Введённый номер строки таблицы истинности (со значением функции true на ней) - " + str(i) + " - превышает номер последней строки - " + str(2**kolarg-1))

numtrue = [int(i) for i in numtrue]
#-----------------------------------
'''for j in range(len(numtrue)-1):
	pyz = 0
	for i in range(j+1, len(numtrue)-1-j):
		if(numtrue[i] > numtrue[i+1]):
			numtrue[i], numtrue[i+1] = numtrue[i+1], numtrue[i]
			pyz = 1
		if(numtrue[len(numtrue)-i-1] < numtrue[len(numtrue)-i-2]):
			numtrue[len(numtrue)-i-1], numtrue[len(numtrue)-i-2] = numtrue[len(numtrue)-i-2], numtrue[len(numtrue)-i-1]
			pyz = 1
		print(numtrue)
	print()
	if(pyz==0):
		print("pyz0")
		break'''
#----------------------------
'''ntrkorz = [0]*max(numtrue)
for i in range(len(numtrue)):
	ntrkorz[numtrue[i]] = 1
numtrue = []
for i in range(len(ntrkorz)):
	if(ntrkorz[i]==1):
		numtrue.append(i)
print(numtrue)'''
#----------------------------
tabist = [0]*max(numtrue)
for i in range(len(numtrue)):
	tabist[numtrue[i]] = 1

'''numstolb = 0
def createTabIst():
	if numstolb < kolarg-1:
		createTabIst()
	'''

tabist = []
for i in range(2**n):
	tabist.append(1 if str(i) in numtrue else 0)

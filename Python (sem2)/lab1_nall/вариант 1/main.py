import math


# def sum_num(a):


# работает неправильно (?)
def expression_func(var1, var2):
	numerator = var1 * var1 + 1.5 * var1 / var2
	numerator = math.log(abs(numerator))
	denominator = 1 / math.sin(var1 + var2)
	denominator += 1 / math.cos(var1 + var2)
	value = numerator / denominator + math.exp(3)
	return round(value, 2)


def years_to_days(years):
	return years * 365


def delivery(storage, store, velocity):
	time = (store - storage) / velocity
	return round(time, 2)


def change(value):
	return int(value % (42 * 2.5))

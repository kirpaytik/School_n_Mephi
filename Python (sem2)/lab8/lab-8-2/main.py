from functools import reduce


def gcd_pair(num1, num2):
    if num1 > num2:
        num1, num2 = num2, num1
    while num1 > 0:
        num2 %= num1
        num1, num2 = num2, num1
    return num2


def gcd(*numbers):
    return reduce(gcd_pair, numbers)

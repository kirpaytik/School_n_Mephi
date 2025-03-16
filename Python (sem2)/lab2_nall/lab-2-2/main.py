def leap_year(year):
    if year % 4 > 0:
        return False
    const400 = 400
    if year % const400 == 0:
        return True
    if year % 100 == 0:
        return False
    if year % 4 == 0:
        return True


def is_perfect(number):
    summ = 0
    for indx in range(1, int(number/2) + 1):
        if number % indx == 0:
            summ += indx
    return number == summ

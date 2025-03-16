import types

numerals = types.MappingProxyType({
    'M': 1000,
    'CM': 900,
    'D': 500,
    'CD': 400,
    'C': 100,
    'XC': 90,
    'L': 50,
    'XL': 40,
    'X': 10,
    'IX': 9,
    'V': 5,
    'IV': 4,
    'I': 1,
})


def to_roman(number):
    roman = ''
    for key in numerals.keys():
        roman += key * (number // numerals[key])
        number %= numerals[key]
    return roman


def is_roman(number, key, count):
    if len(key) == 1:
        if count > 3:
            return 0
        if number[0] != key:
            return 2
    else:
        cond1 = count > 1 or number[:2] != key
        cond2 = len(number) > 2
        cond2 = cond2 and number[2] == key[0]
        if cond1 or cond2:
            return 0
    return 1


def get_key_counted(number, key):
    indx = list(numerals.keys()).index(key)
    count = number.count(key)
    if len(key) == 1 and key != 'I':
        key2 = list(numerals.keys())[indx + 1]
        count -= number.count(key2)
    return count


def to_arabic(number):
    integer = 0
    for key in numerals.keys():
        count = get_key_counted(number, key)
        if count == 0:
            continue
        romanic = is_roman(number, key, count)
        if romanic == 0:
            return False
        if romanic == 2:
            continue
        integer += numerals[key] * count
        number = number.replace(key, '', count)
    if number:
        return False
    return integer

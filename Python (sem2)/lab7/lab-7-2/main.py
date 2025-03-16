import time


def func_decorator(func):
    def wrapper(*args, **kwargs):
        print('Вызов функции:', func.__name__)
        print('Аргументы:', args, kwargs)
        start_time = time.time()
        returned = func(*args, **kwargs)
        end_time = time.time()
        wasted_time = format(end_time - start_time, '.7f')
        print('Время выполнения: {0} сек.'.format(wasted_time))
        print('Результат:', returned)
        return returned
    return wrapper


def is_palindrome(string):
    string2 = ''.join(reversed(string))
    return string == string2


def get_descendant(string):
    number2 = 0
    for index in range(0, len(string), 2):
        number2 *= 10
        number2 += int(string[index])
        number2 += int(string[index + 1])
    return number2


def recursive_palindrome_descendant(number):
    number = str(number)
    if len(number) == 1:
        return False
    if is_palindrome(number):
        return True
    if len(number) % 2 == 1:
        return False
    number2 = get_descendant(number)
    return recursive_palindrome_descendant(number2)


@func_decorator
def palindrome_descendant_rec(number):
    return recursive_palindrome_descendant(number)


@func_decorator
def palindrome_descendant(number):
    number = str(number)
    while len(number) > 1:
        if is_palindrome(number):
            return True
        if len(number) % 2 == 1:
            return False
        number = str(get_descendant(number))
    return False

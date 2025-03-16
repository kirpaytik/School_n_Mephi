import time


def func_decorator(func):
    def wrapper(*args, **kwargs):
        print('Вызов функции:', func.__name__)
        print('Аргументы:', args, kwargs)
        start_time = time.time()
        returned = func(*args, **kwargs)
        end_time = time.time()
        wasted_time = end_time - start_time
        print('Время выполнения: {} сек.'.format(wasted_time))
        print('Результат:', returned)
        return returned
    return wrapper


def func_decorator_rec(func):
    called_times = 0
    
    def wrapper(*args, **kwargs):
        nonlocal called_times
        if called_times == 0:
            print('Вызов функции:', func.__name__)
            print('Аргументы:', args, kwargs)
        called_times += 1
        start_time = time.time()
        returned = func(*args, **kwargs)
        end_time = time.time()
        wasted_time = end_time - start_time
        called_times -= 1
        if called_times == 0:
            print('Время выполнения: {} сек.'.format(wasted_time))
            print('Результат:', returned)
        return returned
    return wrapper


@func_decorator
def is_palindrome(string):
    string2 = ''.join(reversed(string))
    return string == string2


@func_decorator_rec
def is_palindrome_rec(string):
    if len(string) < 2:
        return True
    if string[0] != string[-1]:
        return False
    return is_palindrome_rec(string[1:-1])

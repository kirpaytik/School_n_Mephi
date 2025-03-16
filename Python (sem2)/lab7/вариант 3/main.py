# Сделано для прямоугольной, хотя в условии этого не сказано

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
def reverse_image(matrix):
    return [[1 - number for number in row] for row in matrix]


@func_decorator_rec
def reverse_image_rec(matrix, index=0):
    if index == len(matrix) * len(matrix[0]):
        return matrix
    index1 = index // len(matrix[0])
    index2 = index % len(matrix[0])
    matrix[index1][index2] = 1 - matrix[index1][index2]
    return reverse_image_rec(matrix, index + 1)

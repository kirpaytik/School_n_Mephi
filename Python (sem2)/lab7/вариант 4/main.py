import copy
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


@func_decorator
def move_to_end(src_list, template):
    list1 = [elem for elem in src_list if elem != template]
    list2 = [template for indx in range(src_list.count(template))]
    return list1 + list2


def exclude_templates_rec(src_lst, templ, index=0):
    if index == len(src_lst):
        return src_lst
    if src_lst[index] == templ:
        src_lst.pop(index)
        index -= 1
    return exclude_templates_rec(src_lst, templ, index + 1)


def only_templates_rec(src_lst, templ, index=0):
    if index == len(src_lst):
        return src_lst
    if src_lst[index] != templ:
        src_lst.pop(index)
        index -= 1
    return only_templates_rec(src_lst, templ, index + 1)


@func_decorator
def move_to_end_rec(src_lst, templ):
    list1 = exclude_templates_rec(copy.deepcopy(src_lst), templ)
    list2 = only_templates_rec(copy.deepcopy(src_lst), templ)
    return list1 + list2

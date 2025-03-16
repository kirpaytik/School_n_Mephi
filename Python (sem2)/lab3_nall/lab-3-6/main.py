def plus_sign(string):
    if len(string) == 0:
        return True
    mask = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
    if string[0] in mask or string[-1] in mask:
        return False
    for index in range(1, len(string) - 1):
        cond1 = string[index] in mask
        cond2 = string[index-1] == '+' == string[index+1]
        if cond1 and not cond2:
            return False
    return True

def cond11(wall_bump, index, matrix, numb):
    if (numb == 0):
        cond1 = (wall_bump % 4 == 0)
        offset = (wall_bump + 1) // 4
        length = len(matrix[0])
        cond2 = (index[1] + 1 == length - offset)
        return cond1 and cond2
    cond1 = (wall_bump % 4 == 1)
    offset = (wall_bump + 1) // 4
    length = len(matrix)
    cond2 = (index[0] + 1 == length - offset)
    return cond1 and cond2


def cond33(wall_bump, index, numb):
    if numb == 0:
        cond1 = (wall_bump % 4 == 2)
        offset = (wall_bump + 1) // 4
        cond2 = (index[1] == offset)
        return cond1 and cond2
    cond1 = (wall_bump % 4 == 3)
    offset = (wall_bump + 1) // 4
    cond2 = (index[0] == offset)
    return cond1 and cond2


def condition(wall_bump, index, matrix):
    cond01 = cond11(wall_bump, index, matrix, 0)
    cond02 = cond11(wall_bump, index, matrix, 1)
    cond03 = cond33(wall_bump, index, 0)
    cond04 = cond33(wall_bump, index, 1)
    return cond01 or cond02 or cond03 or cond04


def length_matr(matrix):
    return len(matrix) * len(matrix[0])


def snail_path(matrix):
    direct = [0, 0]
    direct[0] = [0, 1, 0, -1]
    direct[1] = [1, 0, -1, 0]
    wall_bump = 0
    index = [0, 0]
    list_out = [0 for indx in range(length_matr(matrix))]
    for iteration in range(length_matr(matrix)):
        list_out[iteration] = matrix[index[0]][index[1]]
        if condition(wall_bump, index, matrix):
            wall_bump += 1
        index[0] += direct[0][wall_bump % 4]
        index[1] += direct[1][wall_bump % 4]
    return list_out


def rotate(matrix):
    return matrix

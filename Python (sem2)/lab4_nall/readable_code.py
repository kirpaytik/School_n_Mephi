# просто код после исправлений для wemake (flake8) стал нечитаемым, поэтому решил этот для начала сохранить

def snail_path(matrix):
	len_i = len(matrix)
	len_j = len(matrix[0])
	dir_i = [0, 1, 0, -1]
	dir_j = [1, 0, -1, 0]
	dir_ptr, wall_bump, offset = 0, 0, 0
	index1, index2 = 0, 0
	list_out = [0] * len_i * len_j
	for param in range(len_i * len_j):
		list_out[param] = matrix[index1][index2]
		cond1 = (dir_ptr == 0) and (index2 + 1 == len_j - offset)
		cond2 = (dir_ptr == 1) and (index1 + 1 == len_i - offset)
		cond3 = (dir_ptr == 2) and (index2 == 0 + offset)
		cond4 = (dir_ptr == 3) and (index1 == 0 + offset)
		if cond1 or cond2 or cond3 or cond4:
			wall_bump += 1
			offset = (wall_bump + 1) // 4
			dir_ptr = wall_bump % 4
		index1 += dir_i[dir_ptr]
		index2 += dir_j[dir_ptr]
	return list_out

def gen_diff(dict1, dict2):
    dict_res = {}
    for key1 in dict1.keys():
        if (key1 in dict2) == 0:
            dict_res[key1] = 'deleted'
            continue
        if dict1[key1] == dict2[key1]:
            dict_res[key1] = 'unchanged'
        else:
            dict_res[key1] = 'changed'
    for key2 in dict2.keys():
        if (key2 in dict1) == 0:
            dict_res[key2] = 'added'
    return dict_res

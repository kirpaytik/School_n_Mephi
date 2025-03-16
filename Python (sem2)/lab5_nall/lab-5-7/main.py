def merged(dicts):
    dict_res = {}
    for dict_cur in dicts:
        for key, dict_val in dict_cur.items():
            if (key in dict_res) == 0:
                dict_res[key] = set()
            dict_res[key].add(dict_val)
    return dict_res

def same_parity_filter(lst):
    if not lst:
        return []
    templ = lst[0] % 2
    return list(filter(lambda elem: elem % 2 == templ, lst))

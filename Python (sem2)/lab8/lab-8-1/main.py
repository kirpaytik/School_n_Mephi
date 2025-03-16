def filter_anagrams(word, sequence):
    templ = sorted(word)
    return list(filter(lambda elem: sorted(elem) == templ, sequence))

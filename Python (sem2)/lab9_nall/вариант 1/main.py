from glob import glob
import os


def opana(nabr, substring, otvet):
    with open(nabr, 'r') as fstr:
        for line in fstr.readlines():
            if substring in line:
                otvet.append(line)
    return otvet


def grep(substring, fpath):
    otvet = []

    path = fpath[:fpath.rfind('/')]
    fname = fpath[fpath.rfind('/') + 1:]

    if not os.path.isdir(path):
        return otvet

    for nabr in list(glob(os.path.join(path, fname))):
        otvet = opana(nabr, substring, otvet)

    return otvet

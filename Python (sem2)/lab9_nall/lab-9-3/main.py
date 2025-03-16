KEY_LEN = 10
VALUE_LEN = 20


def get_value(path, key):
    with open(path, 'r') as filer:
        data1 = filer.read(KEY_LEN)
        while data1:
            data2 = filer.read(VALUE_LEN)
            if data1 == key:
                return data2
            data1 = filer.read(KEY_LEN)
    return None


def set_value(path, key, record):
    with open(path, 'r+') as filerw:
        data1 = filerw.read(KEY_LEN)
        seek_ptr = KEY_LEN
        while data1:
            if data1 == key:
                filerw.seek(seek_ptr)
                filerw.write(record)
                break
            filerw.read(VALUE_LEN)
            seek_ptr += VALUE_LEN
            data1 = filerw.read(KEY_LEN)
            seek_ptr += KEY_LEN

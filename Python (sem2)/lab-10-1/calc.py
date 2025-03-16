import re
from operator import add, mul, sub, truediv

import prompt
from compf import Compf
from stack import Stack


class Calc(Compf):
    """
    Интерпретатор арифметических выражений вычисляет значения
    правильных арифметических формул, в которых в качестве
    операндов допустимы только цифры [0-7].
    """

    symbols = re.compile(r'[()+\-*/0-7]')

    def __init__(self):
        # Инициализация (конструктор) класса Compf
        super().__init__()
        self.datas = []
        # Создание стека чисел для работы стекового калькулятора
        self.chis = Stack()

    # Интерпретация арифметического выражения
    def compile_calc(self, expression):
        self.datas = Compf.compile(self, expression)
        for opr in self.datas:
            if isinstance(opr, int):
                self.process_val_calc(opr)
            else:
                self.process_oper_calc(opr)
        return self.chis.top()

    # Обработка цифры
    def process_val_calc(self, number):
        self.chis.push(number)

    # Обработка символа операции
    def process_oper_calc(self, operator):
        second, first = self.chis.pop(), self.chis.pop()
        # Use a dictionary to map operators to corresponding functions
        operations = {
            '+': add,
            '-': sub,
            '*': mul,
            '/': truediv,
        }
        res = operations[operator](first, second)
        self.chis.push(res)


if __name__ == '__main__':
    calc = Calc()
    while True:
        str_value = prompt.string('Арифметическое выражение: ')
        print('Результат её компиляции: {0} \n'.format(calc.compile(str_value)))

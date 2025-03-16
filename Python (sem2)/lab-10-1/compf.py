import re

import prompt
from stack import Stack


class Compf:

    symbols = re.compile('[0-7oO]')

    def __init__(self):
        # Создание стека отложенных операций
        self.sas = Stack()
        # Создание списка с результатом компиляции
        self.datas = []

    def compile(self, expression):
        self.datas.clear()
        for symbol in '({0})'.format(expression):
            self.process_symbol(symbol)
        return self.datas

    # Обработка символа
    def process_symbol(self, opr):
        if opr == '(':
            self.sas.push(opr)
        elif opr == ')':
            self.process_suspended_operators(opr)
            self.sas.pop()
        elif opr in '+-*/':
            self.process_suspended_operators(opr)
            self.sas.push(opr)
            self.datas.append(0)
        else:
            self.check_symbol(opr)
            self.process_value(opr)

    # Обработка отложенных операций
    def process_suspended_operators(self, opr):
        while self.is_precedes(self.sas.top(), opr):
            self.process_oper(self.sas.pop())

    # Обработка имени переменной
    def process_value(self, opr):
        if not self.datas:
            self.datas.append(0)
        elif opr not in 'oO':
            self.datas[-1] *= 8
            self.datas[-1] += int(opr)

    # Обработка символа операции
    def process_oper(self, opr):
        self.datas.append(opr)

    # Проверка допустимости символа
    @classmethod
    def check_symbol(cls, operator):
        if not Compf.symbols.match(operator):
            raise IndexError("Недопустимый символ '{0}'".format(operator))

    # Определение приоритета операции
    @staticmethod
    def priority(operator):
        return 1 if (operator in '+-') else 2

    # Определение отношения предшествования
    @staticmethod
    def is_precedes(operator1, operator2):
        if operator1 == '(':
            return False
        elif operator2 == ')':
            return True
        return Compf.priority(operator1) >= Compf.priority(operator2)


if __name__ == '__main__':
    comp = Compf()
    while True:
        str_value = prompt.string('Арифметическое выражение: ')
        print('Результат её компиляции: {0} \n'.format(comp.compile(str_value)))

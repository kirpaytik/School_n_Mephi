from pytest import approx, raises
from calc import Calc


class TestCalc:

    # Инициализация (выполняется для каждого из тестов класса)
    def setup_method(self):
        self.c = Calc()

    # Интерпретатор арифметических выражений работает только с цифрами
    def test_raises(self):
        with raises(IndexError):
            self.c.compile_calc('a')

    # Тесты на сложение
    def test_addition1(self):
        assert self.c.compile_calc('0o1+0o2') == 3

    def test_addition2(self):
        assert self.c.compile_calc('0o1+0o2+0o33+0o4+0o55+0o6') == 85

    def test_addition3(self):
        assert self.c.compile_calc('(0o1+0o2)+(0o33+0o4)') == 34

    def test_addition4(self):
        assert self.c.compile_calc('(0o1+(0o2+0o33)+0o4)') == 34

    # Тесты на вычитание
    def test_subtraction1(self):
        assert self.c.compile_calc('0o1-0o2') == -1

    def test_subtraction2(self):
        assert self.c.compile_calc('0o55-0o2') == 43

    def test_subtraction3(self):
        assert self.c.compile_calc('0o1-0o2-0o33-0o4-0o55-0o6') == -83

    def test_subtraction4(self):
        assert self.c.compile_calc('(0o1-0o2)-(0o33-0o34)') == 0

    # Тесты на умножение
    def test_multiplication1(self):
        assert self.c.compile_calc('0o1*0o2') == 2

    def test_multiplication2(self):
        assert self.c.compile_calc('0o0*0o33') == 0

    def test_multiplication3(self):
        assert self.c.compile_calc('0o7*0o1*0o1*0o1') == 7

    def test_multiplication4(self):
        assert self.c.compile_calc('0o2*0o55*0o2') == 180

    # Тесты на деление
    def test_division1(self):
        assert self.c.compile_calc('0o1/0o2') == approx(0.5)

    def test_division2(self):
        assert self.c.compile_calc('0o2/0o1') == approx(2.0)

    def test_division3(self):
        assert self.c.compile_calc('0o0/0o33') == approx(0)

    def test_division4(self):
        assert self.c.compile_calc('0o10/0o2/0o2/0o2') == approx(1.0)

    def test_division5(self):
        with raises(ZeroDivisionError):
            self.c.compile_calc('0o1/0o0')

    # Тесты на сложные арифметические выражения
    def test_expressions1(self):
        assert self.c.compile_calc('(0o1-0o2)') == -1

    def test_expressions2(self):
        assert self.c.compile_calc('(0o1+0o4)*0o7') == 35

    def test_expressions3(self):
        assert self.c.compile_calc('0o7*(0o10)/0o4') == approx(14.0)

    def test_expressions4(self):
        test = '0o1+0o2+(0o2*(0o3+0o7))/(0o5+0o10/0o3)'
        assert self.c.compile_calc(test) == approx(eval(test))

    def test_expressions5(self):
        test = '(0o3-0o5-0o2*0o6/(0o1+0o1))/(0o2*0o5-0o1+0o4*(0o5*0o2/0o3))+(0o7+0o4+0o7/0o11)/(0o1+0o6/0o3)'
        assert self.c.compile_calc(test) == approx(eval(test))

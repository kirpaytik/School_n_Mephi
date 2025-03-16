from compf import Compf


class TestCompf:

    # Инициализация (выполняется для каждого из тестов класса)
    def setup_method(self):
        self.calc = Compf()

    def form(self, string):
        string = string.split()
        string = [int(i) if i.isdigit() else i for i in string]
        return string

    # Формула из одного символа
    def test_one_symbol(self):
        assert self.calc.compile('0o1') == self.form('1')

    # Формулы с одной операцией
    def test_correct_operations1(self):
        assert self.calc.compile('0o12+0o34') == self.form('10 28 +')

    def test_correct_operations2(self):
        assert self.calc.compile('0o12-0o34') == self.form('10 28 -')

    def test_correct_operations3(self):
        assert self.calc.compile('0o12*0o34') == self.form('10 28 *')

    def test_correct_operations4(self):
        assert self.calc.compile('0o12/0o34') == self.form('10 28 /')

    # Тесты на порядок выполнения операций
    def test_operations_order1(self):
        assert self.calc.compile('0o12+0o56*0o34') == self.form('10 46 28 * +')

    def test_operations_order2(self):
        assert self.calc.compile('0o12*0o34/0o56') == self.form('10 28 * 46 /')

    def test_operations_order3(self):
        assert self.calc.compile('0o12*(0o34/0o56)') == self.form('10 28 46 / *')

    # Тесты на использование скобок
    def test_parentheses1(self):
        assert self.calc.compile('(0o12)') == self.form('10')

    def test_parentheses2(self):
        assert self.calc.compile('(((((0o12))))') == self.form('10')

    def test_parentheses3(self):
        assert self.calc.compile('(((((0o12+0o34))))') == self.form('10 28 +')

    def test_parentheses4(self):
        assert self.calc.compile('(((((((0o12+0o34)*((0o12+0o34)))))))') == self.form('10 28 + 10 28 + *')

    # Тесты на более сложные выражения
    def test_expressions1(self):
        assert self.calc.compile('(0o12+0o34)*0o56+(0o70-0o76)/0o54') == self.form('10 28 + 46 * 56 62 - 44 / +')

    def test_expressions2(self):
        assert self.calc.compile('0o12*(0o12+0o12+0o12+0o12/(0o12-0o12-0o12-0o12))') == \
            self.form('10 10 10 + 10 + 10 10 10 - 10 - 10 - / + *')

    def test_expressions3(self):
        assert self.calc.compile('0o12/0o34*0o56+0o70*0o76/(0o54+0o32)') == \
            self.form('10 28 / 46 * 56 62 * 44 26 + / +')

    def test_expressions4(self):
        assert self.calc.compile('0o12/0o34*(0o56+0o70*0o76)/(0o54+0o32)') == \
            self.form('10 28 / 46 56 62 * + * 44 26 + /')

    def test_expressions5(self):
        assert self.calc.compile('0o12+0o34*(0o56-0o70)*(0o56+(0o70-0o76)/0o12)/0o12') == \
            self.form('10 28 46 56 - * 46 56 62 - 10 / + * 10 / +')

    def test_expressions6(self):
        assert self.calc.compile('((0o3+(0o3*(0o3+(0o3+0o3/0o3)))))/(0o3+0o3)') == \
            self.form('3 3 3 3 3 3 / + + * + 3 3 + /')

    def test_expressions7(self):
        assert self.calc.compile('0o3+(0o3+(0o3*(0o3+(0o3/(0o3*(0o3+0o3))))))') == \
            self.form('3 3 3 3 3 3 3 3 + * / + * + +')

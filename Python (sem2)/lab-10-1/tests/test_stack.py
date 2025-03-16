from pytest import raises
from stack import Stack


class TestStack:

    # Инициализация (выполняется для каждого из тестов класса)
    def setup_method(self):
        self.s = Stack()

    # Сразу после создания стек пуст
    def test_simple1(self):
        assert not self.s.array

    # Простые действия со стеком
    def test_simple2(self):
        self.s.push(1)
        assert self.s.array == [1]
        a = self.s.pop()
        assert a == 1

    # У пустого стека нет верхнего элемента
    def test_empty_stack_top(self):
        s = Stack()
        with raises(IndexError):
            s.top()

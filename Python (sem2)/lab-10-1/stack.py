class Stack:
    """
    Реализация стека на базе вектора
    (для языка Python она тривиальна)
    """

    def __init__(self):
        self.array = []

    def push(self, operand):
        self.array.append(operand)

    def pop(self):
        return self.array.pop()

    def top(self):
        if not self.array:
            raise IndexError('Stack is empty')
        return self.array[-1]

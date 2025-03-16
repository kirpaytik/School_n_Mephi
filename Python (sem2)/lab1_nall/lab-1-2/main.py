import math


def profit(total_sum, binary_purchase):
    return total_sum + int(binary_purchase, base=2)


def frame_rate(minutes, fps):
    return minutes * 60 * fps


def calculate_points(wins, draws, loses):
    return wins * 3 + draws


def expression_func(var1, var2):
    numerator = var1 ** (var2 + 2) + 3 * math.e
    numerator = math.log2(numerator)
    numerator = math.sqrt(numerator)
    denominator = math.log(2 * var1)
    denominator += math.log10(4 * var2)
    return round(numerator / denominator, 2)


def sum_number(num1, num2):
    digit1 = num1 // 100
    digit1 += num2 // 100
    digit1 %= 10
    digit2 = num1 // 10 % 10
    digit2 += num2 // 10 % 10
    digit2 %= 10
    digit3 = num1 % 10
    digit3 += num2 % 10
    digit3 %= 10
    return digit1 * 100 + digit2 * 10 + digit3

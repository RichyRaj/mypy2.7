# Code from: https://realpython.com/python-thinking-recursively
# Only for testing purposes

def sum_recursive(current_number, accumulated_sum):
    # Base case
    if current_number == 11:
        return accumulated_sum
    # Recursive case
    else:
        return sum_recursive(current_number + 1, accumulated_sum + current_number)

# print sum_recursive(1, 0)


def sum_recursive(accumulated_sum, current_number):
    # Base case
    if current_number == 11:
        return accumulated_sum
    # Recursive case
    else:
        return sum_recursive(accumulated_sum + current_number, current_number + 1)

print sum_recursive(0, 1)

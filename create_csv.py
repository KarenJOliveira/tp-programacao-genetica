import csv
import random
import math

# Define the functions F1 through F10 (add the rest of the functions similarly)
def F1(x1, x2):
    denominator = 1.2 + (x2 - 2.5) ** 2

    if denominator == 0:
        return float('inf')  # Return positive infinity or another suitable value

    return math.exp(-(x1 - 1) ** 2) / denominator

def F2(x1, x2):
    return math.exp(-x1) * (x1 ** 3) * math.cos(x1) * math.sin(x1) * (math.cos(x1) * math.sin(2 * x1) - 1) * (x2 - 5)

def F3(x1, x2, x3, x4, x5):
    denominator = 5 + sum((xi - 3) ** 2 for xi in [x1, x2, x3, x4, x5])

    # Check for division by zero
    if denominator == 0:
        return float('inf')  # Return positive infinity or another suitable value

    return 10 / denominator

def F4(x1, x2, x3):
    denominator = x2 ** 2 * (x1 - 10)

    # Check for division by zero
    if denominator == 0:
        return float('inf')  # Return positive infinity or another suitable value

    return 30 * (x1 - 1) * (x3 - 1) / denominator

def F5(x1, x2):
    return 6 * math.sin(x1) * math.cos(x2)

def F6(x1, x2):
    return (x1 - 3) * (x2 - 3) + 2 * math.sin((x1 - 4) * (x2 - 4))

def F7(x1, x2):
    denominator = ((x2 - 2) ** 4 + 10)
    # Check for division by zero
    if denominator == 0:
        return float('inf')  # Return positive infinity or another suitable value

    return (x1 - 3) ** 4 + (x2 - 3) ** 3 - (x2 - 3) / denominator

def F8(x1, x2):
    if x1 == 0 or x2 == 0:
        return float('inf')  # Return positive infinity or another suitable value
    denominator1 = 1 + (x1) ** -4
    denominator2 = 1 + (x2) ** -4

    # Check for division by zero
    if denominator1 == 0 or denominator2 == 0:
        return float('inf')  # Return positive infinity or another suitable value

    return 1 / denominator1 + 1 / denominator2

def F9(x1, x2):
    denominator = 2 - x2
    # Check for division by zero
    if denominator == 0:
        return float('inf')  # Return positive infinity or another suitable value

    return x1 ** 4 - x1 ** 3 + x2 ** 2 / denominator

def F10(x1, x2):
    denominator = 2 + x1 ** 2 + x2 ** 2

    # Check for division by zero
    if denominator == 0:
        return float('inf')  # Return positive infinity or another suitable value

    return 8 / denominator

def F11(x1, x2):
    
    return ((x1 ** 3)/5) + ((x2 ** 3)/2) - x2 - x1

def F12(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10):
    return x1 * x2 + x3 * x4 + x5 * x6 + x1 * x7 * x9 + x3 * x6 * x10

def F13(x1, x2, x3, x4, x5):
    denominator = (3 * x4)

    denominator2 = x5;
    # Check for division by zero
    if denominator == 0 or denominator2 == 0:
        return float('inf')  # Return positive infinity or another suitable value
    return -5.41 + 4.9 * (x4 - x1 + (x2/denominator2)) / denominator

def F14(x1, x2, x3, x4, x5, x6):
    den1 = x2;
    den2 = x4;

    if den1 == 0 or den2 == 0:
        return float('inf')  # Return positive infinity or another suitable value

    denominator = ((x1 / den1) * (x3 / den2))

    # Check for division by zero
    if denominator == 0:
        return float('inf')  # Return positive infinity or another suitable value

    return (x5 * x6) / denominator

def F15(x1, x2, x3, x4, x5):
    denominator = (4 * x4 ** 3 + 5 * x5 ** 4)
    # Check for division by zero
    if denominator == 0:
        return float('inf')  # Return positive infinity or another suitable value

    return 0.81 + 24.3 * (2 * x2 + 3 * x3 ** 2) / denominator

def F16(x1, x2, x3, x4, x5):
    den1 = math.tan(x2);
    den2 = math.tan(x4);

    if den1 == 0 or den2 == 0:
        return float('inf')  # Return positive infinity or another suitable value

    return 32 - 3 * (math.tan(x1) / den1) * (math.tan(x3) / den2)

def F17(x1, x2, x3, x4, x5):
    denominator = math.sin(x4)
    if denominator == 0:
        return float('inf')  # Return positive infinity or another suitable value
    return 22 - 4.2 * (math.cos(x1) - math.tan(x2)) * (math.tanh(x3) / denominator)

def F18(x1, x2, x3, x4, x5):
    return x1 * x2 * x3 * x4 * x5

def F19(x1, x2, x3, x4, x5):
    denominator = math.exp(x2)
    if denominator == 0:
        return float('inf')  # Return positive infinity or another suitable value
    return 12 - 6 * (math.tan(x1) / denominator) * (x3 - math.tan(x4))

def F20(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10):
    denominators = [xi for xi in [x1, x2, x3, x4, x5, x6, x7, x8, x9, x10] if xi != 0]

    # Check if there are any non-zero denominators
    if not denominators:
        return float('inf')  # Return positive infinity or another suitable value

    return sum(1 / xi for xi in denominators)


def F21(x1, x2, x3, x4, x5):
    return 2 - 2.1 * math.cos(9.8 * x1) * math.sin(1.3 * x5)


# Number of rows and range for random values
num_rows = 50000
value_range = (-5, 5)

lista1 = [F2, F8]
lista2 = [2,8]
# Generate and write data for each function
for i,func in zip(lista2, lista1):
    # Generate random data
    sample_data = []
    for _ in range(num_rows):
        x_values = [random.randint(*value_range) for _ in range(func.__code__.co_argcount)]
        row_data = x_values + [func(*x_values)]
        sample_data.append(row_data)

    # File name for the CSV file
    
    csv_file_name = f'function_{i}_50k_data.csv'

    # Generating CSV file
    with open(csv_file_name, 'w', newline='') as csvfile:
        # Creating a CSV writer object
        csv_writer = csv.writer(csvfile)

        # Writing header
        
        header = [f'x{j}' for j in range(1, func.__code__.co_argcount + 1)] + [f'F{i}']
        
        csv_writer.writerow(['rows', num_rows])
        csv_writer.writerow(['columns', len(header)])

        csv_writer.writerow(header)

        # Writing data
        csv_writer.writerows(sample_data)

    print(f"CSV file '{csv_file_name}' has been generated successfully.")

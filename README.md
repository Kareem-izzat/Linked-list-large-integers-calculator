# Large Integer Calculator

## Overview
This project is an application of Linked Lists, where you will implement a large integer calculator. Performing arithmetic on very large numbers (i.e., numbers with a large number of digits) is an inherent problem in computers as floating-point representations are subject to overflow. This application will perform arithmetic on very large integers using linked lists. The program supports addition, subtraction, multiplication, and division of arbitrarily large integers.

## Features
- **Addition**: Perform addition of two very large integers.
- **Subtraction**: Perform subtraction of two very large integers.
- **Multiplication**: Standard multiplication where the first multiplicand is multiplied with each digit of the second multiplicand and then added.
- **Division**: Implemented as long division. Includes a function to determine if the dividend is larger than the divisor in absolute value.
- **File Input**: Reads a file containing at least two numbers to perform the operations above.
- **Menu System**: Allows the user to select the operations through a proper menu with options to run the program's functionalities (i.e., read the input file, add, subtract, multiply, divide, print the results to an output file, and exit).

## Implementation Details
- Each integer is represented as a list of its digits.
- Proper handling and manipulation of linked lists to perform arithmetic operations on large integers.

## Usage

### Menu Options
1. Read the input file
2. Add
3. Subtract
4. Multiply
5. Divide
6. Print the results to an output file
7. Exit

### Input/Output File
- Ensure the input/output file names are consistent with the specifications.
#### division needs some inhancments in this version

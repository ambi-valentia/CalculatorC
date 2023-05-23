# CalculatorC

A caluculator written in C. Uses the Reverse Polish Notation, stack, supports basic math operations, trigonometric, logarithmic and user defined functions.

Based on the work of a singly linked linear list, a stack was developed, duplicated for separate storage of operations and numbers.

Functions were written to convert the input string to the form of a string in reverse Polish notation (this function is called recursively if necessary) and the calculation module (function 'process').

To count the number of opening and closing brackets, the brkt variable is introduced, which increases by one with each opening bracket and decreases with each closing one.

Checking the elements of a string in reverse Polish notation for a number, operation and functions is written in separate functions (as well as functions for performing basic operations: addition, multiplication, subtraction, division, exponentiation and factorial).

To carry out the calculation, the program, depending on the operation, pops one or more numbers from the stack of numbers, and from the stack of operations - an operation, after which the calculation is performed, and its result is put back on the stack of numbers. As a result, instead of one or two raw numbers, there is one on the stack - the result of the calculation, and the operation that the program has already performed disappears from the stack of operations.

The priority of operations is determined at the stage of translation into reverse Polish notation using switch in the CheckUrPrivilege function.

#include "postfix.h"


// NB: Will return -1 if an arg is neither a number or an operand
// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char **args, int nargs)
{
    // Write your code here
    struct double_stack *stack = double_stack_new(nargs);
    for (int i = 0; i < nargs; i++)
    {
        if (isdigit(args[i][0]) || isdigit(args[i][1]))
        {
            char *ptr;
            double value = strtod(args[i], &ptr);
            double_stack_push(stack, value);
        }
        else
        {
            double num2 = double_stack_pop(stack);
            double num1 = double_stack_pop(stack);
            if (args[i][0] == '+')
                double_stack_push(stack, num1 + num2);
            else if (args[i][0] == '-')
                double_stack_push(stack, num1 - num2);
            else if (args[i][0] == 'X')
                double_stack_push(stack, num1 * num2);
            else if (args[i][0] == '/')
                double_stack_push(stack, num1 / num2);
            else if (args[i][0] == '^')
                double_stack_push(stack, pow(num1, num2));
            else return -1; // ERROR CASE - Bad input
        }
    }
    return double_stack_pop(stack);
}

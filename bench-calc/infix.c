#include "infix.h"

int precedence(char op)
{
    if (op == '^') {
        return 3;
    }
    else if (op == 'X' || op == '/') {
        return 2;
    }
    else
        return (op == '+' || op == '-') ? 1 : 0;
}

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char **args, int nargs)
{
    // Write your code here
    struct double_stack *stack = double_stack_new(nargs);
    char **output_string = malloc(sizeof(char *) * nargs);
    int output_length = 0;
    for (int i = 0; i < nargs; i++)                                                    // for each token in the input string
    {                                                                                  // {
        if (isdigit(args[i][0]) || isdigit(args[i][1]))                                //   if (token is a number)
        {                                                                              //   {
            output_string[output_length] = args[i];                                    //     append token to output string
            output_length++;                                                           //
        }                                                                              //   }
        else if (args[i][0] == '(')                                                    //   else if (token is a left bracket)
        {                                                                              //   {
            double_stack_push(stack, args[i][0]);                                      //     push bracket to stack
        }                                                                              //   }
        else if (precedence((char)args[i][0]) != 0)                                    //   else if (token is an operator)
        {                                                                              //   {
            while (precedence((char) stack->items[stack->top - 1]) >= precedence(args[i][0]))                   //     while (there is operator  op  on top of the stack  AND op has equal or higher precedence than token)
            {                                                                          //       {
                char *ptr = malloc(sizeof(char) * 2);                                  //         pop stack
                ptr[0] = (char) double_stack_pop(stack);                               //         convert (double) operator to char * (output_string is an array of char*)
                ptr[1] = '\0';                                                         //
                output_string[output_length] = ptr;                                    //         append char* operator to output string
                output_length++;                                                       //
            }                                                                          //       }
            double_stack_push(stack, args[i][0]);                                      //       push token operator to stack
        }                                                                              //    }
        else if (args[i][0] == ')')                                                    //    else if (token is a right bracket)
        {                                                                              //    {
            while (stack->items[stack->top - 1] != '(')                                //      while (top of stack != left bracket)
            {                                                                          //      {
                char *ptr = malloc(sizeof(char) * 2);                                  //         pop operator from stack
                ptr[0] = (char) double_stack_pop(stack);                               //         convert (double) operator to char * (output_string is an array of char*)
                ptr[1] = '\0';                                                         //
                output_string[output_length] = ptr;                                    //         append char* operator to output string
                output_length++;                                                       //
            }                                                                          //       }
            double_stack_pop(stack);                                                   //     pop left bracket
        }                                                                              //    }
    }
    while (stack->top != 0)                                                            //    while (stack has remaining items)
    {                                                                                  //    {
        char *ptr = malloc(sizeof(char) * 2);                                          //         pop item from stack
        ptr[0] = (char) double_stack_pop(stack);                                       //         convert (double) item to char * (output_string is an array of char*)
        ptr[1] = '\0';                                                                 //
        output_string[output_length] = ptr;   //         append char* item to output string
        output_length++;                      //    }
    }
    return evaluate_postfix_expression(output_string, output_length);
}

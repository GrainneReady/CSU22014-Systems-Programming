#include "stack.h"

struct double_stack *double_stack_new(int max_size)
{
    struct double_stack *result;

    result = malloc(sizeof(struct double_stack));
    result->max_size = max_size;
    result->top = 0;
    // allocate space for the data stored in the stack
    result->items = malloc(sizeof(double) * max_size);
    // return a pointer to the newly-allocated stack
    return result;
}

// push a value onto the stack
void double_stack_push(struct double_stack *this, double value)
{
    if (this->top < this->max_size)
    {
        this->items[this->top] = value;
        ++this->top; // point to next available space
    }
    else
    {
        // Full :(
    }
}

// pop a value from the stack
// NB: Returns -1 when Stack is Empty
// NB: Pointer will always point to next available space in the stack, which is why you need to decrement to get to the last pushed value
double double_stack_pop(struct double_stack *this)
{
    if (this->top > 0)
    {
        this->top--;
        return this->items[this->top];
    } // else Empty :(, return -1
    return -1;
}

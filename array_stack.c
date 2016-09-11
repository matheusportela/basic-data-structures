/**
 * Implementation of array-based stack, following the approach explained at
 * Introduction to Algorithms - Cormen et. al (Chapter 10), for didactic
 * purposes.
 *
 * Author: Matheus V. Portela (matheus.v.portela@gmail.com)
 */
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 4

/*
 * Array-based stack struct, with fixed number of elements and fixed data type.
 */
struct stack_s {
    unsigned int top;
    char data[STACK_SIZE];
};

/*
 * Print information on the stack, such as current size, emptiness, and
 * fullness.
 */
void print_stack(struct stack_s stack);

/*
 * Initialize stack to avoid errors based on different compiler implementations.
 */
void init_stack(struct stack_s* stack);

/*
 * Whether the stack is full.
 */
int is_full(struct stack_s stack);

/*
 * Whether the stack is empty.
 */
int is_empty(struct stack_s stack);

/*
 * Push new data to the stack or raise an error if it is full.
 */
void push(struct stack_s* stack, char data);

/*
 * Pop new data from the stack or raise an error if it is empty.
 */
char pop(struct stack_s* stack);

int main() {
    struct stack_s stack;

    init_stack(&stack);
    print_stack(stack);

    push(&stack, 'a');
    print_stack(stack);

    push(&stack, 'b');
    print_stack(stack);

    push(&stack, 'c');
    print_stack(stack);

    push(&stack, 'd');
    print_stack(stack);

    for (int i = 0; i < STACK_SIZE; i++) {
        printf("Pop: %c\n", pop(&stack));
        print_stack(stack);
    }

    return 0;
}

void print_stack(struct stack_s stack) {
    printf("Stack\n");
    printf("  size: %d\n", stack.top);
    printf("  empty: %d\n", is_empty(stack));
    printf("  full: %d\n", is_full(stack));
}

void init_stack(struct stack_s* stack) {
    stack->top = 0;
}

int is_full(struct stack_s stack) {
    return (stack.top == STACK_SIZE);
}

int is_empty(struct stack_s stack) {
    return (stack.top == 0);
}

void push(struct stack_s* stack, char data) {
    if (is_full(*stack)) {
        fprintf(stderr, "Stack error: Cannot push to full stack\n");
        exit(1);
    }

    stack->data[stack->top] = data;
    stack->top++;
}

char pop(struct stack_s* stack) {
    if (is_empty(*stack)) {
        fprintf(stderr, "Stack error: Cannot pop from empty stack\n");
        exit(1);
    }

    stack->top--;
    return stack->data[stack->top];
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun_stack.h"

list *stack_head = NULL;

int top_of_funstack(void) {
    if (stack_head == NULL) {
        fprintf(stderr, "Stos jest pusty!\n");
        return -1; 
    }
    return stack_head->par_level;
}

void put_on_fun_stack(int par_level, char *funame) {
    list *new_node = (list *)malloc(sizeof(list));
    if (new_node == NULL) {
        fprintf(stderr, "Błąd alokacji pamięci!\n");
        exit(EXIT_FAILURE);
    }
    new_node->par_level = par_level;
    new_node->funname = strdup(funame);
    new_node->next = stack_head;
    stack_head = new_node;
}

char *get_from_fun_stack(void) {
    if (stack_head == NULL) {
        fprintf(stderr, "Stos jest pusty!\n");
        return NULL;
    }
    list *temp = stack_head;
    char *funname = strdup(stack_head->funname);
    stack_head = stack_head->next;

    free(temp->funname);
    free(temp);
    return funname;
}

void print_stack(list *head) {
    printf("Zawartosc stosu:\n");
    while (head != NULL) {
        printf("Funname: %s, Par_level: %d\n", head->funname, head->par_level);
        head = head->next;
    }
}

int main(void) {
    put_on_fun_stack(1, "main");
    put_on_fun_stack(2, "function_a");
    put_on_fun_stack(3, "function_b");
    printf("Top of stack par_level: %d\n", top_of_funstack());
    print_stack(stack_head);
    char *funname = get_from_fun_stack();
    printf("Zdjeto funkcje: %s\n", funname);
    free(funname);
    print_stack(stack_head);
    while (stack_head != NULL) {
        char *name = get_from_fun_stack();
        free(name);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun_stack.h"

// Głowa listy stosu
list *stack_head = NULL;

// Implementacja funkcji z pliku nagłówkowego

int top_of_funstack(void) {
    if (stack_head == NULL) {
        fprintf(stderr, "Stos jest pusty!\n");
        return -1; // Wartość wskazująca błąd
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
    new_node->funname = strdup(funame); // Kopiowanie nazwy funkcji
    new_node->next = stack_head;
    stack_head = new_node;
}

char *get_from_fun_stack(void) {
    if (stack_head == NULL) {
        fprintf(stderr, "Stos jest pusty!\n");
        return NULL;
    }
    list *temp = stack_head;
    char *funname = strdup(stack_head->funname); // Kopiowanie nazwy funkcji
    stack_head = stack_head->next;

    free(temp->funname);
    free(temp);
    return funname;
}

void print_stack(list *head) {
    printf("Zawartość stosu:\n");
    while (head != NULL) {
        printf("Funname: %s, Par_level: %d\n", head->funname, head->par_level);
        head = head->next;
    }
}

// Funkcja główna

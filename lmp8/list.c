#include <stdio.h>
#include <stdlib.h>
#include <string.h> // exit - ale exit trzeba kiedyś usunąć i nie będzie to potrzebne
#include "alex.h"       // analizator leksykalny
#include "fun_stack.h"
#include "list.h"


typedef struct e {
    int par_level;        
    char *funname;       
    struct e *next;       
} list;


static list *stack_head = NULL;


int top_of_funstack(void) {
    if (stack_head == NULL) {
        return -1; // Stos pusty
    }
    return stack_head->par_level;
}

/**
 * Funkcja odkłada na stos parę (par_level, funname).
 * @param par_level - Zagłębienie nawiasowe
 * @param funname - Nazwa funkcji (kopiowana do stosu)
 */
void put_on_fun_stack(int par_level, char *funname) {

    list *new_elem = (list *)malloc(sizeof(list));
    if (!new_elem) {
        perror("Error: malloc failed");
        exit(EXIT_FAILURE); 
    }

    
    new_elem->par_level = par_level;
    new_elem->funname = strdup(funname); 
    if (!new_elem->funname) {
        perror("Error: strdup failed");
        free(new_elem);
        exit(EXIT_FAILURE);
    }
    new_elem->next = stack_head;
    stack_head = new_elem;
}

/**
 * Funkcja usuwa wierzchołek stosu i zwraca nazwę funkcji (funname).
 * @return Nazwa funkcji (funname) lub NULL, jeśli stos jest pusty.
 */
char *get_from_fun_stack(void) {
    if (stack_head == NULL) {
        return NULL; 
    }
    list *top_elem = stack_head;
    char *funname = strdup(top_elem->funname); 
    stack_head = top_elem->next;
    free(top_elem->funname);
    free(top_elem);

    return funname;
}

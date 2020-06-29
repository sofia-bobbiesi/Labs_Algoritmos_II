#include <stdio.h> /* printf()...           */
#include "list.h"  /* Interfaz del TAD list */

static void
print_list(list l) {
    /* Muestra por pantalla una lista de enteros */
    /*
     * Es crucial que list_index() esté bien programada
     */
    printf("[");
    for (unsigned int i=0u; i < list_length(l); i++) {
        printf("%i", list_index(l, i));
        if (i != list_length(l) - 1)  {
            printf(", ");
        }
    }
    printf("]");
}

static void
show_status(list l, const char *name) {
    /*
     * Muestra por pantalla: - La etiquena 'name'
     *                       - El contendio de la lista
     *                       - Su longitud
     *                       - Si es o no vacía
     */
    /* Se muestra la etiqueta */
    printf("{ %s == ", name);
    /* Se muestra el contenido de la lista */
    print_list(l);
    printf(" /\\ ");
    /* Se muestra la longitud */
    printf("|%s| = %i /\\ ", name, list_length(l));
    /* Se indica si es vacía o no */
    if (list_is_empty(l)) printf("empty"); else printf("not empty");
    printf(" }");
    printf("\n\n");
}

int main(void) {
    list l, l2;
    /* Construimos las listas l y l2 */
    l = list_empty();
    l2 = list_empty();

    /* Mostramos el estado de l */
    printf("l = list_empty(l)\n");
    show_status(l, "l");
    /* Agregamos un elemento a l y vemos que pasa */
    l = list_addl(l, 5);
    printf("l = list_addl(l, 5)\n");
    show_status(l, "l");
    /* Agregamos varios elementos a l y vemos que pasa */
    l = list_addl(list_addl(l, 8), 2);
    printf("l = list_addl(2, list_addl(l, 5))\n");
    show_status(l, "l");
    /* Agregamos un elemento por la derecha a l y vemos que pasa */
    l = list_addr(l, -1);
    printf("l = list_addr(l, -1)\n");
    show_status(l, "l");
    /* Probamos tomar 2 elementos de l y vemos que pasa */
    l = list_take(l, 2);
    printf("l = list_take(l, 2)\n");
    show_status(l, "l");
    /* Agregamos valores a l2 */
    l2 = list_addl(list_addl(list_addl(l2, 10), 11), 12);
    show_status(l2, "l2");
    /* Probamos concatenarle a l la lista l2*/
    l = list_concat(l, l2);
    printf("l = list_concat(l, l2)\n");
    show_status(l, "l");

    l = list_destroy(l);
    l2 = list_destroy(l2);
    return 0;
}

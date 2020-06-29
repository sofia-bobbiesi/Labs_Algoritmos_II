#include <stdio.h>   /* printf()...                   */
#include <stdlib.h> /* Librería estándar             */
#include "set.h"   /* Interfaz del TAD set          */
#include <time.h> /* Manipulación del tiempo/fecha */


static void
print_set(set s) {
    /* Muestra por pantalla el contenido de un conjunto de enteros */
    /*
     * Es crucial que las funciones:
     *   - set_copy()
     *   - set_get()
     *   - set_elim()
     *   - set_is_empty()
     *
     * estén bien programadas para que se muestre correctamente.
     */
    set saux=set_copy(s);
    printf("{");
    while (!set_is_empty(saux)) {
        type_elem e;
        e = set_get(saux);
        printf("%i", e);
        saux = set_elim(saux, e);
        if (!set_is_empty(saux))
            printf(", ");
     }
    printf("}");
    saux = set_destroy(saux);
}

static void
show_status(set s, const char *name) {
    /*
     * Muestra por pantalla: - La etiquena 'name'
     *                       - El contendio del conjunto
     *                       - Su longitud
     *                       - Si es o no vacío
     */
    /* Se muestra la etiqueta */
    printf("{ %s == ", name);
    /* Se muestra el contenido del conjunto */
    print_set(s);
    printf(" /\\ ");
    /* Se muestra el cardinal */
    printf("|%s| = %i /\\ ", name, set_cardinal(s));
    /* Se indica si es vacío o no */
    if (set_is_empty(s)) printf("empty"); else printf("not empty");
    printf(" }");
    printf("\n\n");
}
int main(){ 
 


    /* Construimos los conjuntos s y s2 */
    set s = set_empty();
    set s2 = set_empty();

    /* Mostramos el estado de s */
    printf("s = set_empty(s)\n");
    show_status(s, "s"); 

    /* Mostramos el estado de s2 */
    printf("s2 = set_empty(s2)\n");
    show_status(s, "s2");

    /* Generamos una 'semilla' aleatoria para obtener 
    diferentes números cada vez que se corra el programa */
    srand(time(NULL)); 

    /* Agregamos una cantidad random de numeros desde -50 hasta 50
    una cantidad n random de veces, variando entre 0 y 10 */
    int n = rand() % 11;
    for( int i = 0 ; i < n ; i++ ) {
        s = set_add(s,(rand() % 101) - 50);
    }
    show_status(s, "s"); 

    /* Implementamos el mismo proceso para s2 */
    int m = rand() % 11;
    for(int i = 0 ; i < m ; i++ ) {
        s2 = set_add(s2,(rand() % 101) - 50);
    }
    show_status(s2, "s2"); 

    /*Probamos unir a s el conjunto s2 */
    set s_u = set_copy(s);
    s_u = set_union(s_u,s2);
    printf("s_u = set_union(s,s2)\n");
    show_status(s_u, "s ∪ s2"); 

    /* Probamos intersectar a s el conjunto s2 */
    set s_i = set_copy(s);
    s_i = set_inters(s_i,s2);
    printf("s_i = set_inters(s,s2)\n");
    show_status(s_i,"s ∩ s2"); 

    /* Probamos calcular la diferencia entre s y el conjunto s2 */
    set s_d = set_copy(s);
    s_d = set_dif(s_d,s2);
    printf("s_d = set_dif(s,s2)\n");
    show_status(s_d,"s dif s2");

    /* Destruimos los conjuntos y sus copias */
    s = set_destroy(s);
    s2 = set_destroy(s2); 
    s_u = set_destroy(s_u);
    s_i = set_destroy(s_i);
    s_d = set_destroy(s_d);
   
    return 0;
}


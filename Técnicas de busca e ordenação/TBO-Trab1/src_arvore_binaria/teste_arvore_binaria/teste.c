#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../aresta.h"
#include "../arvore_binaria.h"
#include "../vertice.h"

int main(int argc, char *argv[])
{
    ArvoreBinaria *ab = arvore_binaria_construct();

    //  1
    // 0 2
    Vertice *um = vertice_construct(1);
    vertice_set_distancia_origem(um, 1.0);
    arvore_binaria_push(ab, um);

    Vertice *zero = vertice_construct(0);
    vertice_set_distancia_origem(zero, 0.0);
    arvore_binaria_push(ab, zero);

    Vertice *dois = vertice_construct(2);
    vertice_set_distancia_origem(dois, 2.0);
    arvore_binaria_push(ab, dois);

    // 2
    printf("0.00 %.2f\n", vertice_get_distancia_origem((Vertice *)arvore_binaria_pop_min(ab))); // 0.00
    printf("1.00 %.2f\n", vertice_get_distancia_origem((Vertice *)arvore_binaria_pop_min(ab))); // 1.00

    //        2
    //    1       5
    //  0       3   6
    //           4
    arvore_binaria_push(ab, um);
    arvore_binaria_push(ab, zero);

    Vertice *cinco = vertice_construct(5);
    vertice_set_distancia_origem(cinco, 5.0);
    arvore_binaria_push(ab, cinco);

    Vertice *tres = vertice_construct(3);
    vertice_set_distancia_origem(tres, 3.0);
    arvore_binaria_push(ab, tres);

    Vertice *quatro = vertice_construct(4);
    vertice_set_distancia_origem(quatro, 4.0);
    arvore_binaria_push(ab, quatro);

    Vertice *seis = vertice_construct(6);
    vertice_set_distancia_origem(seis, 6.0);
    arvore_binaria_push(ab, seis);

    //                2
    //        1               3
    //    0                       4
    //                              6
    //                             5
    arvore_binaria_remove(ab, cinco);
    arvore_binaria_push(ab, cinco);

    //        2 
    //    1       4
    //  0           6
    //             5
    arvore_binaria_remove(ab, tres);

    //        0 
    //            4
    //              6
    //             5
    arvore_binaria_remove(ab, dois);
    arvore_binaria_remove(ab, um);

    //    4 
    //      6
    //     5
    arvore_binaria_remove(ab, zero);

    //        4 
    //    0       6
    //      1   5
    //       2
    arvore_binaria_push(ab, zero);
    arvore_binaria_push(ab, um);
    arvore_binaria_push(ab, dois);

    //                0 
    //                        1
    //                            2
    //                              6
    //                             5
    arvore_binaria_remove(ab, quatro);

    //
    printf("0.00 %.2f\n", vertice_get_distancia_origem((Vertice *)arvore_binaria_pop_min(ab))); // 0.00
    printf("1.00 %.2f\n", vertice_get_distancia_origem((Vertice *)arvore_binaria_pop_min(ab))); // 1.00
    printf("2.00 %.2f\n", vertice_get_distancia_origem((Vertice *)arvore_binaria_pop_min(ab))); // 2.00
    printf("5.00 %.2f\n", vertice_get_distancia_origem((Vertice *)arvore_binaria_pop_min(ab))); // 5.00
    printf("6.00 %.2f\n", vertice_get_distancia_origem((Vertice *)arvore_binaria_pop_min(ab))); // 6.00

    // free
    vertice_destroy(um);
    vertice_destroy(zero);
    vertice_destroy(dois);
    vertice_destroy(tres);
    vertice_destroy(quatro);
    vertice_destroy(cinco);
    vertice_destroy(seis);
    arvore_binaria_destroy(ab);

    return 0;
}
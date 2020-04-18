//
//  TP_OPENMP_4.c
//  
//
//  Created by Srinath_SC on 05/04/2020.
//
// To compile it use
// clang -Xpreprocessor -fopenmp -lomp TP_OPENMP_4.c  -o TP_OPENMP_4.out
//

#include "TP_OPENMP_4.h"

int i;
#pragma omp threadprivate(i)
int main()
{ i = -1;
#pragma omp parallel
    {
#pragma omp single copyprivate(i)
        { i = 4; }
        int tnum = omp_get_thread_num();
        printf("La valeur parallele est %d\n Le numero de thread est %d\n", i, tnum);
    }
    printf("La valeur sequentielle est %d\n", i);
}

/**** Observation ****/
/*
 BARRIRE DE SYNCHRONISATION
 En testant le code nous constatons que la valeur parallèle et la valeur séquentielle sont égales quel que soit le changement de .
 Ceci est dû au fait que les données privées ne sont accessibles que par le thread correspondant.
 On constate à l'affichage du numéro de thread qu'il évolue de 0 à 7 sur notre machine.
 */

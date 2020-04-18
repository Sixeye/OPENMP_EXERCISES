//
//  TP_OPENMP_02.c
//  
//
//  Created by Srinath_SC on 10/03/2020.
//
// to compile it in macOS : clang -Xpreprocessor -fopenmp -lomp file.c -o file.out
//

#include "TP_OPENMP_02.h"

int main()
{
    int i = -1;
    printf("Je suis le thread main du no: %2d\n", omp_get_thread_num());
    printf("La valeur de la variable locale à main dans la région séquentielle est : %2d\n", i);
    omp_set_num_threads(5);
#pragma omp parallel
    {
        int j;
        i = omp_get_thread_num();
        
        /* Question 3  */
#pragma omp for
        for(j=0;j<X;j++)
        {
            printf("La valeur la variable locale à main dans la région parallèle est : %2d\n", i);
            
        }
        printf("Je suis le thread main du numéro: %2d\n", omp_get_thread_num());
        printf("La valeur la variable locale à main dans la région séquentielle est %2d\n", i);
    }
    return 0;
}

/*  Question 1 et 2
 */
/*
 (i)
 Le main thread reste 0 sinon la plupart s’exécute sur un thread, le 1, sauf au départ ou il a été exécuté sur le thread 4, 3, 2  et 0.
 Le problème est qu'il reste majoritairement sur un thread, le 1.
 
 (ii)
 On l’exécute avec X définit à 100 :
 
 Je ne copie pas le résultat ici car il est quasi identique à l'exception près qu'il y a plus de processus. On constate par ailleurs qu'il y a toujours le même soucis ou le thread 1 est majoritairement utilisé.
 
 On l’exécute avec X à 1000 :
 
 On constate la même chose pas forcément sur le thread 1 mais on constate que la majorité est exécuté sur un thread.
 On constate la même chose ici.
 
(iii)
 La solution serait de diviser la valeur de X par 2  et de déclarer deux boucles for.
 */


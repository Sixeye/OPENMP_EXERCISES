//
//  TP_OPENMP_03.c
//  
//
//  Created by Srinath_SC on 25/03/2020.
//
// to compile it in macOS : clang -Xpreprocessor -fopenmp -lomp file.c -o file.out
//

#include "TP_OPENMP_03.h"


/****  Question 1  ****/
//Dans les threadprivate i vaut 0 sauf dans le premier le thread, le 0, la variable dans la région séquentielle i vaut -1;

/*
 
 int i;
 #pragma omp threadprivate(i)
 int main()
 {
 i = -1;
 #pragma omp parallel
 {
 printf("La valeur de la variable threadprivate du Thread %2d est %2d\n", omp_get_thread_num(), i);
 }
 printf("La valeur de la variable dans la région séquentielle est %d\n", i);
 }
 
*/

/****  Question 2  ****/
//Ici i vaut toujours -1 quelque soit le thread. La variable de i est copiée dans chaque thread.

/*
 
int i;
#pragma omp threadprivate(i)
int main()
{
    i = -1;
#pragma omp parallel copyin(i)
    {
        printf("La valeur de la variable threadprivate du Thread %2d est %2d\n", omp_get_thread_num(), i);
    }
    printf("La valeur de la variable dans la région séquentielle est %d\n", i);
}
 
*/

/****  Question 3  ****/
//Je n'ai pas saisi la question


/****  Question 4  ****/
// Chaque thread a sa variable i qui semble contenir n'importe quelle valeur car i n'est pas initialisé. A la fin de l'exécution, il ne reste plus que la variable i de main.


int main()
{
    int i = -1;
    #pragma omp parallel private(i)
    {
        
        printf("La valeur de la variable threadprivate du Thread %2d est %2d\n", omp_get_thread_num(), i);
        }
    
    printf("La valeur de la variable dans la région séquentielle est %d\n", i);
     
}

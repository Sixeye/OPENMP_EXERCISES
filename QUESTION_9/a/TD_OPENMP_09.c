//
//  TD_OPENMP_09.c
//  
//
//  Created by Srinath_SC on 12/04/2020.
//
// To compile it use
// clang -Xpreprocessor -fopenmp -lomp TD_OPENMP_09.c  -o TD_OPENMP_09.out
//

#include "TD_OPENMP_09.h"

void carre(long int *tab, int n)
{
    int i = 0;
    long int total = 0;
    // On définit le nombre de thread(s)
    omp_set_num_threads(n);
    
    #pragma omp parallel for
    for (i=0; i < n; i++) {
        tab[i] *= tab[i];
        total += tab[i];
    }
    printf("Total = %ld \n", total);
}


int main()
{
    long int *tab = NULL;
    int i,n;
    
    printf("Entrez n, la dimension: \n");
    scanf("%d",&n);
    tab = malloc(sizeof(long int)*n);
    
    srand(time(NULL));
    #pragma omp parallel for
    for (i=0; i<n; ++i)
        tab[i] = (rand() % 100);
    
    
    carre(tab, n);
    
}


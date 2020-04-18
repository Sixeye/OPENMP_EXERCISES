//
//  TD_OPENMP_11.c
//  
//
//  Created by Srinath_SC on 12/04/2020.
//
// clang -Xpreprocessor -fopenmp -lomp TD_OPENMP_11.c  -o TD_OPENMP_11.out

#include "TD_OPENMP_11.h"

void swap(int *a, int *b)
{
    int bulle = *a;
    *a = *b;
    *b = bulle;
}

void quicksort(int *v, int deb, int fin)
{
    if (deb < fin)
    {
        int pivot = v[deb];
        int separ = deb;
        int i;
        
        printf("Thread %d de %d a %d\n", omp_get_thread_num(), deb, fin);
        for(i = deb + 1; i<= fin; ++i)
        {
            if (v[i] < pivot)
            {
                ++separ;
                swap(&v[i], &v[separ]);
            }
        }
        swap (&v[deb], &v[separ]);
        #pragma omp parallel sections shared(v)
        {
        #pragma omp section
            {
                quicksort(v, deb, separ -1);
            }
        #pragma omp section
            {
                quicksort(v, separ + 1, fin);
            }
        }
    }
}

void affiche(int *tab, int taille)
{
    int i;
    printf("[");
    for (i=0; i<taille; i++)
        printf("%d, ",tab[i]);
    printf("]\n");
}

int main()
{
    int i;
    int v[N];
    srand(time(NULL));
    
    for(i=0; i<N; i++)
    {
        v[i] = rand() % 1000;
    }
    printf("Tableau original\n");
    affiche(v, N);
    
    quicksort(v, 0, N-1);
    printf("\n Tableau trie \n");
    affiche(v, N);
}

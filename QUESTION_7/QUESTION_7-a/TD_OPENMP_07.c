//
//  TD_OPENMP_07.c
//  
//
//  Created by Srinath_SC on 11/04/2020.
//
// To compile it use
// clang -Xpreprocessor -fopenmp -lomp TD_OPENMP_07.c  -o TD_OPENMP_07.out
//

#include "TD_OPENMP_07.h"

void pmat(int resultat[], int matrice[][3], int vecteur[], int n){
    int i, j;
#pragma omp parallel
#pragma omp for
    for(i=0 ; i<n ; i++){
        resultat[i]=0;
    }
#pragma omp for
    for(i=0 ; i<n ; i++){
        for(j=0 ; j<n ; j++){
            resultat[i] = resultat[i] + (matrice[i][j])*(vecteur[j]);
        }
    }
}

int main(){
    int A[3][3] = { {2, 2, 2},
        {3, 3, 3},
        {4, 4, 4} };
    int V[3] = {2, 2, 2};
    int B[3];
    int i;
    
    int C[3];
    pmat(B,A,V,3);
    
    printf("\n");
#pragma omp parallel
#pragma omp for
    {
        for(i=0 ; i<3 ; i++){
            printf("%d ",B[i]);
            printf("\n");
        }
    }
    return 0;
}

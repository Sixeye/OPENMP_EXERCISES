//
//  TP_OPENMP_01_2.c
//  
//
//  Created by Srinath_SC on 10/03/2020.
//
//to compile it in macOS : clang -Xpreprocessor -fopenmp -lomp file.c
//

#include "TP_OPENMP_01_2.h"

int main()
{
    printf("Suite de la question 1, le debut est dans un autre dossier. \n");
    omp_set_num_threads(2);
#pragma omp parallel
    {
        int i = 0;
#pragma omp for
        for(i=0;i<10;i++){
            printf("iteration %d\n",i);
            printf("Bienvenue le monde depuis le thread numero %d\n", omp_get_thread_num());
        }
    }
}

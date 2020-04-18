//
//  TP_OPENMP_01.c
//  
//
//  Created by Srinath_SC on 10/03/2020.
// to compile it in macOS : clang -Xpreprocessor -fopenmp -lomp file.c
//

#include "TP_OPENMP_01.h"

/* Question 1.1
 */
/*
int main()
{
    int ID = 0;
    printf("Bonjour le monde (%d)", ID);
    printf("Bonjour le monde (%d) \n", ID);
}

 */
/*  Question 1.2
 */


int main()
{
    printf("Suite de la question 1, le debut de la question est commentée. \n");
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

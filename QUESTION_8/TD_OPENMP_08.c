//
//  TD_OPENMP_08.c
//  
//
//  Created by Srinath_SC on 11/04/2020.
//
// To compile it use
// clang -Xpreprocessor -fopenmp -lomp TD_OPENMP_08.c  -o TD_OPENMP_08.out
//


#include "TD_OPENMP_08.h"


// Définitions des fonctions utilisées
void poly_one_thr(int nthr, int A, int x);
void poly_mult_thr(int nthr, int A, int x);


// Main
int main() {
    
    int A, x, y; // A*(A*x+x)+x
    int nthr; // Nombre de Threads
    
    printf("Combien de threads voulez-vous? \n");
    scanf("%d",&nthr);
    printf("Définissez A, du polynôme y=A*(A*x+x)+x : \n");
    scanf("%d",&A);
    printf("Définissez x, du polynôme y=A*(A*x+x)+x : \n");
    scanf("%d",&x);
    
    // si les arguments sont bons, on définit nthr et n
    if(nthr > 0 && x > 0 && A > 0){
        printf("Le nombre de thread(s) est %d, A est %d et x est %d :", nthr, A, x);
    }
    else {
        // Si les paramètres ne sont pas corrects.
        printf("\n Mauvaises données, nous allons présumer que nous avons 4 threads, A égal à 5 et x égal à 6.");
        
        nthr=4; A = 5; x = 6;
    }
    
    // Si l'utilisateur ne spécifie qu'un thread nous n'utiliserons pas omp
    // Sinon nous effectuons une parallèlisation des tâches avec
    // la fonction qui intègre omp
    if (nthr == 1){
        poly_one_thr(nthr,A,x);
    }
    else {
        poly_mult_thr(nthr,A,x);
    
    printf("Fait.\n");
    }
    return 0;
}

// fin du main()

// Un thread pas d'omp
void poly_one_thr(int nthr, int A, int x) // A*(A*x+x)+x résultat)
{
    int y;
    double temp_exec_debut, temp_exec_fin, temp_exec;
    
    temp_exec_debut = omp_get_wtime();
 
    y = A*(A*x+x)+x;
    
    printf("voici le résultat: y= %d \n", y);
    
    temp_exec_fin = omp_get_wtime();
    temp_exec = temp_exec_fin - temp_exec_debut;
    printf("Voici le temps du début : %fl\n", temp_exec_debut);
    printf("Voici le temps de fin : %fl\n", temp_exec_fin);
    printf("Voici le temps d'execution : %fl\n", temp_exec);
    
} // fin de poly_one_thr

// poly_mult_thr() est la fonction où l'on utilise omp parallel
//  nthr est le nombre de threads
void poly_mult_thr(int nthr, int A, int x)
{
    int y;
    double temp_exec_debut, temp_exec_fin, temp_exec;
    
    temp_exec_debut = omp_get_wtime();
    
    #pragma omp parallel shared (A,x)
    {
        y = A*(A*x+x)+x;
    }
    printf("voici le résultat: y= %d \n", y);
    
    temp_exec_fin = omp_get_wtime();
    temp_exec = temp_exec_fin - temp_exec_debut;
    printf("Voici le temps du début : %fl\n", temp_exec_debut);
    printf("Voici le temps de fin : %fl\n", temp_exec_fin);
    printf("Voici le temps d'execution : %fl\n", temp_exec);

} // fin de poly_mult_thr()

// Question b dans le fichier PDF

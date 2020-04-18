//
//  TD_OPENMP_07b.c
//  
//
//  Created by Srinath_SC on 11/04/2020.
//
// To compile it use
// clang -Xpreprocessor -fopenmp -lomp TD_OPENMP_07b.c  -o TD_OPENMP_07b.out
//

#include "TD_OPENMP_07b.h"


// Définitions des fonctions utilisées
void matrice_mult(double *A, double *B, double *result, int n);
void matrice_mult_thr(double *A, double *B, double *result, int n, int nthr);
void fprint_matrice(char flnm[], double *mat, int dim);
void rand_matrice(double *mat, int n);

// Main
int main() {
    
    double *A=NULL, *B=NULL, *C=NULL; // C=A*B C résultat
    int nthr; // Nombre de Threads
    int n;  // dimension de la matrice
    printf("Combien de threads voulez-vous? \n");
    scanf("%d",&nthr);
    printf("Définissez n, la dimension de la matrice: \n");
    scanf("%d",&n);
    
    // si les arguments sont bons, on définit nthr et n
    if(nthr > 0 && n > 0)
        printf("Le nombre de thread(s) est %d et la matrice est de dimension %d :", nthr, n);
    else {
        // Si les paramètres ne sont pas corrects.
        printf("\n Mauvaises données, nous allons présumer que nous avons 4 threads et une matrice de dimension 3.");

        nthr=4; n =3;
    }
    
   
    
    // Allocation de la mémoire
    A = (double *)malloc(n*n*sizeof(double));
    if(A==NULL) printf("\n Impossible d'allouer de la mémoire à la matrice 1.\n");
    B = (double *)malloc(n*n*sizeof(double));
    if(B==NULL) printf("\n Impossible d'allouer de la mémoire à la matrice 2.\n");
    C = (double *)malloc(n*n*sizeof(double));
    if(C==NULL) printf("\n Impossible d'allouer de la mémoire à la matrice 3.\n");
    
    // Nous préparons les deux matrices à multiplier A et B
    printf("\n Nous construisons les deux matrices...");
    srand( (unsigned int)time(NULL) );
    printf("A (%d x %d)...",n,n);
    rand_matrice(A, n);
    printf("Fait. B (%d x %d)...",n,n);
    rand_matrice(B, n);
    printf("Fait.\n");
    
    
    printf("On multiplie les matrices... \n");
    
    // Si l'utilisateur ne spécifie qu'un thread nous allons faire une simple multiplication
    // Sinon nous effectuons une parallèlisation de la multiplication en
    // utilisant la fonction qui intègre omp
    if (nthr == 1)
        matrice_mult(A,B,C,n);
    else
        matrice_mult_thr(A,B,C,n,nthr);
    
    printf("Fait.\n");
    
    
    // On edite pour chaque matrice un fichier texte avec le résultat
    fprint_matrice("A.txt",A,n);
    fprint_matrice("B.txt",B,n);
    fprint_matrice("C.txt",C,n);

    
    
    // Libération des mallocs
    free(A);
    free(B);
    free(C);
    
    return 0;
}

// fin du main()

// matrice_mult() effectue la méthode carré
//  A et B sont les matrices qui seront multipliées
//  result est la matrice résultat
//  n est le nombre d'entrée(s)(ligne(s)) et colonne(s)
void matrice_mult(double *A, double *B, double *result, int n)
{
    int i,j,k;
    double temp_exec_debut, temp_exec_fin, temp_exec;
    
    temp_exec_debut = omp_get_wtime();
    
    for(i=0; i<n; i++) // itération avec nos entrée(s)
        for(j=0; j<n; j++) // itération avec les colonnes
        {
            *( result+(j+i*n) ) = 0; // initialisation
            
            // itération entre les colonne(s) et entrée(s) de chaque matrice
            for(k=0; k<n; k++)
                *( result+(j+i*n) ) += *( A+(k+i*n) )*( *( B+(j+k*n) ));
        }
    
    temp_exec_fin = omp_get_wtime();
    temp_exec = temp_exec_fin - temp_exec_debut;
    printf("Voici le temps du début : %fl\n", temp_exec_debut);
    printf("Voici le temps de fin : %fl\n", temp_exec_fin);
    printf("Voici le temps d'execution : %fl\n", temp_exec);
    
} // fin de matrice_mult

//matrice_mult_thr() est la fonction où l'on utilise omp parallel
//  A et B seront multiplées
//  result est le résultat
//  n est le nombre d'entrée(s)(ligne(s)) et colonne(s)
//  nthr est le nombre de threads
void matrice_mult_thr(double *A, double *B, double *result, int n, int nthr)
{
    int part_rows, th_id;
    double temp_exec_debut, temp_exec_fin, temp_exec;
    part_rows = n/nthr;
    
    temp_exec_debut = omp_get_wtime();
    
    // On définit le nombre de thread(s)
    omp_set_num_threads(nthr);
    #pragma omp parallel shared(A,B,result,part_rows) private(th_id)
    {
        int i,j,k; //iterators
        th_id = omp_get_thread_num(); // th_id a le numéro de thread pour chaque thread
        
        // On sépare le premier pour parallèliser les threads
        
    #pragma omp for schedule(guided,part_rows)
        for(i=0; i<n; i++)
        {
            printf("Le thread #%d s'occupe de la ligne numéro %d.\n",th_id,i);
            
            for(j=0; j<n; j++)
            {
                *( result+(j+i*n) ) = 0; //initialize
                
                for(k=0; k<n; k++)
                    *( result+(j+i*n) ) += *( A+(k+i*n) )*( *( B+(j+k*n) ));
            }
        }
    }
    
    temp_exec_fin = omp_get_wtime();
    temp_exec = temp_exec_fin - temp_exec_debut;
    printf("Voici le temps du début : %fl\n", temp_exec_debut);
    printf("Voici le temps de fin : %fl\n", temp_exec_fin);
    printf("Voici le temps d'execution : %fl\n", temp_exec);
    
} // fin de matrice_mult_thr()

// fprint_matrice() editera les matrices dans les fichiers concernés

void fprint_matrice(char flnm[], double *mat, int n)
{
    int i,j;
    FILE *fl;
    
    fl = fopen(flnm,"w"); // on ouvre le fichier pour y écrire
    
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            fprintf(fl,"%1.4f ",*( mat+(j+i*n) ));
        
        fprintf(fl,"\n");
    }
    
    fclose(fl); // On ferme le fichier, l'écriture y est terminée
} // fin de fprint_matrice()


// rand_mat() créé une matrice carré aléatoire de dimension n
void rand_matrice(double *mat, int n)
{
    int i,j;
    
    for(i=0; i<n; i++) // itération lignes
        for(j=0; j<n; j++) //itération colonnes
            *(mat+(j+i*n)) = (10.0*rand())/RAND_MAX;
} // fin de rand_matrice()

// Question c dans le fichier pdf

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define N 100 // Tamaño de las matrices

/**
 * Imprime una matriz de tamaño N x N en la consola.
 */
void print_matriz(long matriz[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%ld ", matriz[i][j]);
        }
        printf("\n");
    }
}
void print_matrizI(int matriz[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", matriz[i][j]); // Imprime el valor de cada elemento de la matriz
        }
        printf("\n"); // Agrega un salto de línea al final de cada fila
    }
}
/**
 * Función principal del programa.
 */
int main(int argc, char **argv)
{
    int num_procs, rank, num = 1;
    // Inicializa las matrices A, B y C
    int a[N][N], b[N][N];
    long c[N][N];
    MPI_Init(&argc, &argv);                    // Inicializa el entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); // Obtiene el número total de procesos en ejecución
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);      // Obtiene el rango (ID) del proceso actual

    if (rank == 0)
    {                      // Si el proceso actual es el proceso maestro (rango 0)
        srand(time(NULL)); // Genera una semilla para la función rand() basada en el tiempo actual
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                a[i][j] = num; // rand() % 10; // Genera un valor aleatorio entre 0 y 9 para cada elemento de la matriz a
                b[i][j] = num; // rand() % 10; // Genera un valor aleatorio entre 0 y 9 para cada elemento de la matriz b
                num++;
            }
        }

        printf("matriz A:\n");
        print_matrizI(a); // Imprime la matriz a
        printf("matriz B:\n");
        print_matrizI(b); // Imprime la matriz b
    }

    MPI_Bcast(a, N * N, MPI_INT, 0, MPI_COMM_WORLD); // Transmite la matriz a a todos los procesos
    MPI_Bcast(b, N * N, MPI_INT, 0, MPI_COMM_WORLD); // Transmite la matriz b a todos los procesos

    int chunk_size = N / num_procs; // Calcula el tamaño del fragmento (chunk) de la matriz que cada proceso va a procesar
    int start = rank * chunk_size;  // Calcula el índice de inicio del fragmento de la matriz que el proceso actual va a procesar
    int end = start + chunk_size;   // Calcula el índice de fin del fragmento de la matriz que el proceso actual va a procesar

    for (int i = start; i < end; i++) // Itera sobre las filas del fragmento de la matriz que el proceso actual va a procesar
    {
        for (int j = 0; j < N; j++) // Itera sobre las columnas de la matriz
        {
            c[i][j] = 0;                // Inicializa el valor del elemento de la matriz resultante a cero
            for (int k = 0; k < N; k++) // Itera sobre las columnas de la matriz a y las filas de la matriz b
            {
                c[i][j] += a[i][k] * b[k][j]; // Multiplica los elementos correspondientes de a , b y los suma a la posición correspondiente de la matriz resultado c
            }
        }
    }
    // Reúne todos los datos de la matriz resultado c en el proceso 0.
    MPI_Gather(c + start, chunk_size * N, MPI_LONG, c, chunk_size * N, MPI_LONG, 0, MPI_COMM_WORLD);
    // El proceso 0 imprime la matriz resultado c
    if (rank == 0)
    {
        printf("matriz C:\n");
        print_matriz(c);
    }
    MPI_Finalize(); // Finaliza MPI
    return 0;       // fin de programa
}
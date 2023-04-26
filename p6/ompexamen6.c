#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
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
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

/**
 * Función principal del programa.
 */
int main()
{
    // Inicializa las matrices A, B y C
    int num = 1;
    int a[N][N], b[N][N];
    long c[N][N];
    // Inicializa el generador de números aleatorios con una semilla diferente en cada ejecución
    srand(time(NULL));

    // Llena las matrices A y B con números aleatorios entre 0 y 9
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            a[i][j] = num; // rand() % 10;
            b[i][j] = num; // rand() % 10;
            num++;
        }
    }

    // Imprime las matrices A y B en la consola
    printf("matriz A:\n");
    print_matrizI(a);
    printf("matriz B:\n");
    print_matrizI(b);

    // Realiza la multiplicación de matrices en paralelo utilizando OpenMP
#pragma omp parallel for shared(a, b, c) schedule(static)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            c[i][j] = 0;
            // Multiplica los elementos de la fila i de A por los elementos de la columna j de B
            for (int k = 0; k < N; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    // Imprime la matriz resultante C en la consola
    printf("matriz C:\n");
    print_matriz(c);

    // fin de programa
    return 0;
}

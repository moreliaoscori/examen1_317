#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <gmp.h>

int main(int argc, char** argv) {
    int rank, size;
    mpz_t a, b, c, temp;
    mpz_init(a); // Inicializa las variables a, b, c y temp con valor 0
    mpz_init(b);
    mpz_init(c);
    mpz_init(temp);

    MPI_Init(&argc, &argv); // Inicializa el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtiene el rango (identificador) del proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtiene el número total de procesos en ejecución

    if (rank == 0) { // Proceso maestro
        mpz_set_ui(a, 0); // Inicializa a = 0 y b = 1 para empezar la serie de Fibonacci
        mpz_set_ui(b, 1);
        gmp_printf("%Zd\n%Zd\n", a, b); // Imprime los dos primeros números de la serie

        for (int i = 2; i <= 1000; i++) { // Calcula y muestra los números siguientes de la serie
            mpz_add(c, a, b);
            gmp_printf("%Zd\n", c);
            mpz_set(a, b);
            mpz_set(b, c);
        }
    } else { // Procesos esclavos
        for (int i = rank; i <= 1000; i += size - 1) { // Cada proceso esclavo calcula un subconjunto de la serie
            mpz_set_ui(a, 0); // Inicializa a = 0 y b = 1 para empezar la serie de Fibonacci
            mpz_set_ui(b, 1);

            for (int j = 2; j <= i; j++) { // Calcula el número i-ésimo de la serie
                mpz_add(c, a, b);
                mpz_set(temp, a);
                mpz_set(a, b);
                mpz_set(b, c);
            }
            MPI_Send(&c, sizeof(mpz_t), MPI_BYTE, 0, 0, MPI_COMM_WORLD); // Envía el resultado al proceso maestro
        }
    }

    mpz_clear(a); // Libera la memoria asignada a las variables
    mpz_clear(b);
    mpz_clear(c);
    mpz_clear(temp);

    MPI_Finalize(); // Finaliza el entorno MPI

    return 0;
}

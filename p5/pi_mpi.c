#include <mpi.h>              // Incluye la biblioteca de MPI
#include <stdio.h>            // Incluye la biblioteca estándar de entrada y salida

#define NUM_ITERATIONS 1000   // Número de iteraciones para calcular la integral
#define DELTA_X 1.0 / NUM_ITERATIONS  // Tamaño del intervalo

int main(int argc, char* argv[]) {
  int rank, size;            // Variables para almacenar el rank y el número total de procesos

  MPI_Init(&argc, &argv);    // Inicializa MPI
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Obtiene el rank del proceso actual
  MPI_Comm_size(MPI_COMM_WORLD, &size);  // Obtiene el número total de procesos

  int block_size = NUM_ITERATIONS / size;  // Tamaño de cada bloque de iteraciones
  int start_index = rank * block_size;     // Índice de inicio del bloque actual
  int end_index = start_index + block_size - 1;  // Índice final del bloque actual

  double sum = 0.0;          // Variable para almacenar la suma parcial de cada proceso
  double x;                  // Variable para el cálculo de la integral

  for (int i = start_index; i <= end_index; i++) {  // Cada proceso calcula una parte de la integral
    x = (i + 0.5) * DELTA_X;
    sum += 4.0 / (1.0 + x * x);
  }

  double pi;                 // Variable para el valor final de Pi
  MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);  // Reduce las sumas parciales en el proceso 0 y obtiene el valor final de Pi

  if (rank == 0) {           // El proceso 0 imprime el resultado
    pi *= DELTA_X;
    printf("El valor de Pi es: %f\n", pi);
  }

  MPI_Finalize();            // Finaliza MPI
  return 0;                 // Sale del programa
}

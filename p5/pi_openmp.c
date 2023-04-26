#include <omp.h> // Incluye la biblioteca OpenMP
#include <stdio.h>

#define NUM_ITERATIONS 1000 // Define una constante NUM_ITERATIONS con valor 1000
#define DELTA_X 1.0 / NUM_ITERATIONS // Define una constante DELTA_X como 1 / NUM_ITERATIONS

int main() {
  double sum = 0.0; // Inicializa la variable sum en 0
  double x;

  #pragma omp parallel for reduction(+:sum) // Inicia una región paralela con un bucle for y una cláusula reduction para sumar los resultados
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    x = (i + 0.5) * DELTA_X; // Calcula el valor de x
    sum += 4.0 / (1.0 + x * x); // Suma el resultado de 4 / (1 + x^2) a la variable sum
  }

  double pi = sum * DELTA_X; // Calcula el valor de Pi

  printf("El valor de Pi es: %f\n", pi); // Imprime el valor de Pi

  return 0; // Termina la ejecución del programa
}
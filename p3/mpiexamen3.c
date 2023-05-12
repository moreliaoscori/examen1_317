#include <stdio.h>
#include <string.h>
#include <mpi.h>

int isPalindrome(char *word, int start, int end) {
    while (start < end) {
        if (word[start] != word[end])
            return 0;
        start++;
        end--;
    }
    return 1;
}

int main(int argc, char **argv) {
    int rank, size, len;
    char word[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Ingrese una palabra: ");
        scanf("%s", word);
        len = strlen(word);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(word, len, MPI_CHAR, 0, MPI_COMM_WORLD);

    int start = rank * len / size;
    int end = (rank + 1) * len / size - 1;

    int localPalindrome = isPalindrome(word, start, end);

    int globalPalindrome;
    MPI_Reduce(&localPalindrome, &globalPalindrome, 1, MPI_INT, MPI_LAND, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        if (globalPalindrome)
            printf("verdad.\n", word);
        else
            printf("falso\n", word);
    }

    MPI_Finalize();
    return 0;
}

// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    char *buffer = malloc(
        HEADER_SIZE); // criei uma variável temporária pra armazenar o valor de entrada do cabeçalho

    fread(buffer, 1, HEADER_SIZE, input);   // passada do cabeçalho para buffer
    fwrite(buffer, 1, HEADER_SIZE, output); // passada de buffer para output
    free(buffer); // importante pra não pegar memória da rapaziada de harvard lol

    int16_t sample; // variável int com 2 bytes ao invés de 4

    while (fread(&sample, 2, 1, input) == 1) // looping que para quando a função for igual a 0, ou
                                             // seja, quando ela terminar as unidades
    {
        sample = sample * factor;      // multiplica pra mudar o volume
        fwrite(&sample, 2, 1, output); // passa o valor multiplicado para o output que já contem o
                                       // cabeçalho, agora o programa roda por inteiro
    }
    // Close files
    fclose(input);
    fclose(output); // fecha os arquivos pra não dar erro
}

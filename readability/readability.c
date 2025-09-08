#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string texto = get_string("Texto: ");

    int letras = 0;
    int palavras = 1; // para que não haja erros de a última palavra sem espaço
    int frases = 0;

    for (int i = 0; i < strlen(texto); i++)
    {
        if (isalpha(texto[i]))
        {
            letras++;
        }
        if (isspace(texto[i]))
        {
            palavras++;
        }
        if (texto[i] == '.' || texto[i] == '!' || texto[i] == '?')
        {
            frases++;
        }
    }

    float L = (float) letras / palavras * 100;
    float S = (float) frases / palavras * 100;

    float resultado = 0.0588 * L - 0.296 * S - 15.8;

    if (resultado >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (resultado < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(resultado));
    }
}

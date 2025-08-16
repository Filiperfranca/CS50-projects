#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int main(void)
{
    int pontos[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}; //contabilização de pontos por letra

    string jogador1 = get_string("Jogador 1 digite sua palavra: ");
    string jogador2 = get_string("jogador 2 digite sua palavra: "); //entrada dos jogadores

    int pontos_jogador1 = 0;
    int pontos_jogador2 = 0;

    for (int i = 0; jogador1[i] != '\0'; i++) //verificação do primeiro jogador
    {
        char letra_atual1 = jogador1[i];

        if (isalpha(letra_atual1))
        {
            pontos_jogador1 += pontos[toupper(jogador1[i]) - 'A']; // toupper deixa todas as entradas em maiusculo, e então, na tablesa ASCII ele remove o numero A 97 criando uma ordem de 0-26 para usarmos de indice para soma de pontos
        }
    }

    for (int j = 0; jogador2[j] != '\0'; j++)
    {
        chat letra_atual2 = jogador2[j]

        if (isalpha(letra_atual2))
        {
            pontos_jogador2 += pontos[toupper(jogador2[j]) - 'A'];
        }
    }

    printf("\n"); // pra ficar mais bonito

    if (pontos_jogador1 < pontos_jogador2)
    {
        printf("Player 2 wins!\n");
        printf("pontuação:\n");
        printf("jogador 2: %i\n", pontos_jogador2);
        printf("jogador 1: %i\n", pontos_jogador1);
    }
    else if (pontos_jogador2 < pontos_jogador1)
    {
        printf("Player 1 wins!\n");
        printf("pontuação:\n");
        printf("jogador 1: %i\n", pontos_jogador1);
        printf("jogador 2: %i\n", pontos_jogador2);
    }
    else
    {
        printf("Tie!\n");
        printf("pontuação:\n");
        printf("jogador 1: %i\n", pontos_jogador1);
        printf("jogador 2: %i\n", pontos_jogador2);
    }
}

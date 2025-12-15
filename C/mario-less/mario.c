#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int altura;
    do
    {
        altura = get_int("digite a altura aqui: "); // entrada da altura da piramide
    }
    while (altura < 1); // se o valor da piramide for menos que 1. ele volta para o "do" e pede novamente

    for (int j = 1; j <= altura; j++) // laço principal que define cada linha
    {

        for (int k = 0; k < altura - j; k++) // laço dos espaços, ele pega o valor de j subtrai da altura e imprime o valor de espaços que sempre vai 1 menor que j
        {
            printf(" ");
        }

        for (int i = 0; i < j; i++) //ele imprime o valor de j só que em "#"
        {
            printf("#");
        }

        printf("\n");
    }
}

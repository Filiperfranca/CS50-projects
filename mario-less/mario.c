#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int altura;
    do
    {
        altura = get_int("digite a altura aqui: ");
    }
    while(altura < 1);

    for (int j = 1; j <= altura; j++)
    {

        for (int k = 0; k < altura - j; k++)
        {
            printf(" ");
        }

        for (int i = 0; i < j; i++)
        {
            printf("#");
        }

        printf("\n");
        
    }

}

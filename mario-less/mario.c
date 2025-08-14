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

    for (int i = 1; i <= altura; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }

}

#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // definição de variáveis fixas, o que não as torna uma variavel, evitando os magic numbers
#define quarters 25
#define dimes 10
#define nickels 5
#define pennies 1

    int troco;
    do
    {
        troco = get_int("digite o valor do troco: ");
    }
    while (troco < 0); // checkpoint pra não ter troco menor 0

    int moedas_usadas = 0;

    moedas_usadas = troco / quarters; // calculo do troco junto com a quantidade de moedas

    troco = troco % quarters;

    moedas_usadas = moedas_usadas + (troco / dimes);

    troco = troco % dimes;

    moedas_usadas = moedas_usadas + (troco / nickels);

    troco = troco % nickels;

    moedas_usadas = moedas_usadas + (troco / pennies);

    troco = troco % pennies;

    printf("foram usadas %i moedas\n", moedas_usadas); // foram usadas tantas moedas
}

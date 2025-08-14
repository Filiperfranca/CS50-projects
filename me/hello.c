#include <cs50.h>
#include <stdio.h>

// inicia o programa
int main(void)
{
    string nome =
        get_string("digite seu nome: "); // variável de texto string para digitar o seu nome

    printf("hello, %s\n",
           nome); // imprime no terminal seu nome usando o %s, com o \n para mudar de linha
}

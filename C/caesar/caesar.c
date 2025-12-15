#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int only_digits(string a)
{
    for (int i = 0; a[i] != '\0'; i++)
    {
        if (a[i] < '0' || a[i] > '9')
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, string argv[])
{

    if (argc == 2 && only_digits(argv[1]))
    {
        int key = atoi(argv[1]);

        string frase = get_string("plaintext: ");

        for (int j = 0; frase[j] != '\0'; j++)
        {
            if (frase[j] >= 'a' && frase[j] <= 'z')
            {
                frase[j] = (frase[j] - 'a' + key) % 26 + 'a';
            }
            else if (frase[j] >= 'A' && frase[j] <= 'Z')
            {
                frase[j] = (frase[j] - 'A' + key) % 26 + 'A';
            }
        }

        printf("ciphertext: %s\n", frase);
        return 0;
    }

    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

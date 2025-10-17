// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

int palavras_contadas = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int indice = hash(word);

    while()

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int tamanho = strlen(word);
    long soma = 0;

    for (int i = 0; i < tamanho; i++)
    {
        soma += toupper(word[i]);
    }

    if (tamanho == 0)
    {
        return 0;
    }

    long media = soma / tamanho;
    return media % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dicionario = fopen(dictionary, "r");
    if (dicionario == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];

    while (fscanf(dicionario, "%s", buffer) != EOF)
    {
        node *nova_palavra = malloc(sizeof(node));
        if (nova_palavra == NULL)
        {
            fclose(dicionario);
            return false;
        }

        palavras_contadas++;
        strcpy(nova_palavra->word, buffer);

        unsigned int indice = hash(nova_palavra->word);

        nova_palavra->next = table[indice];
        table[indice] = nova_palavra;
    }

    fclose(dicionario);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return palavras_contadas;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}

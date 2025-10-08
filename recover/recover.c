#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("linha de comando: ./recover card.raw\n");
        return 1;
    }
    if (strcmp(argv[1], "card.raw") != 0)
    {
        printf("você está no cs50, use  linha de comando: ./recover card.raw\n");
        return 1;
    }

    FILE *imagem = fopen(argv[1], "r");
    if (imagem == NULL)
    {
        printf("erro ao tentar abrir arquivo\n");
        return 2;
    }

    unsigned char buffer[512];

    int foto = 0;
    char arquivo_nome[8];
    FILE *arquivo_saida = NULL;

    while (fread(buffer, 512, 1, imagem) == 1)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (foto > 0)
            {
                fclose(arquivo_saida);
            }
            sprintf(arquivo_nome, "%03i.jpg", foto);
            foto++;
            arquivo_saida = fopen(arquivo_nome, "wb");
        }

        if (arquivo_saida != NULL)
        {
            fwrite(buffer, 512, 1, arquivo_saida);
        }
    }
    fclose(arquivo_saida);
    fclose(imagem);
    printf("concluído!\n");
    return 0;
}

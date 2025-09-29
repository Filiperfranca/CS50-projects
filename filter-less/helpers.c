#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE azul_original = image[i][j].rgbtBlue;
            BYTE vermelho_original = image[i][j].rgbtRed;
            BYTE verde_original = image[i][j].rgbtGreen;

            int conversão = round(((float)azul_original + vermelho_original + verde_original) / 3.0);

            image[i][j].rgbtBlue = conversão;
            image[i][j].rgbtRed = conversão;
            image[i][j].rgbtGreen = conversão;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE azul_original = image[i][j].rgbtBlue;
            BYTE vermelho_original = image[i][j].rgbtRed;
            BYTE verde_original = image[i][j].rgbtGreen;

            int sepia_vermelho = round(.393 * vermelho_original + .769 * verde_original + .189 * azul_original);
            int sepia_verde = round(.349 * vermelho_original + .686 * verde_original + .168 * azul_original);
            int sepia_azul = round(.272 * vermelho_original + .534 * verde_original + .131 * azul_original);

            if(sepia_vermelho > 255)
            {
                sepia_vermelho = 255;
            }
            if(sepia_verde > 255)
            {
                sepia_verde = 255;
            }
            if(sepia_azul > 255)
            {
                sepia_azul = 255;
            }

            image[i][j].rgbtBlue = sepia_azul;
            image[i][j].rgbtRed = sepia_vermelho;
            image[i][j].rgbtGreen = sepia_verde;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

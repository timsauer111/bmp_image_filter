#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE *avg = malloc(sizeof(BYTE));

            if (avg == NULL)
            {
                printf("Error");
                return;
            }

            *avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3;
            image[i][j].rgbtBlue = *avg;
            image[i][j].rgbtGreen = *avg;
            image[i][j].rgbtRed = *avg;
            free(avg);
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
            BYTE *sepiaRed = malloc(sizeof(BYTE));
            BYTE *sepiaGreen = malloc(sizeof(BYTE));
            BYTE *sepiaBlue = malloc(sizeof(BYTE));

            if (sepiaRed == NULL || sepiaGreen == NULL || sepiaBlue == NULL)
            {
                printf("Error");
                return;
            }

            *sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            *sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            *sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtBlue = *sepiaBlue > 255 ? 255 : *sepiaBlue;
            image[i][j].rgbtGreen = *sepiaGreen > 255 ? 255 : *sepiaGreen;
            image[i][j].rgbtRed = *sepiaRed > 255 ? 255 : *sepiaRed;
            free(sepiaBlue);
            free(sepiaGreen);
            free(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE *tmp = malloc(sizeof(RGBTRIPLE)*width);
        if (tmp == NULL)
        {
            printf("Error");
            return;
        }
        for (int j = 0; j < width; j++)
        {
            tmp[j] = image[i][j];
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[width-j];
        }
        free(tmp);
    }

    return;
}

// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 1; i < height-1; i++)
    {
        for (int j = 1; j < width-1; j++)
        {
            BYTE sumRed = copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed;
            BYTE sumGreen = copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen;
            BYTE sumBlue = copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue;
            image[i][j].rgbtRed = round(sumRed / 9);
            image[i][j].rgbtGreen = round(sumGreen / 9);
            image[i][j].rgbtBlue = round(sumBlue / 9);
        }
    }

    return;
}


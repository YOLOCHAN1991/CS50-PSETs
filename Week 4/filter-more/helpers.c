#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Gets average and assigns it to images' bytes.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned short avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Inverts row
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < width - j - 1; k++)
            {
                RGBTRIPLE temp = image[i][k];
                image[i][k] = image[i][k + 1];
                image[i][k + 1] = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Make copy of image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Box blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // First row
            if (i == 0)
            {
                // Upper left corner
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed
                                                 + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 4.0);
                    image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue
                                                  + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 4.0);
                    image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen
                                                   + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 4.0);
                }
                // Upper Right corner
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed
                                                 + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) / 4.0);
                    image[i][j].rgbtBlue = round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue
                                                  + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 4.0);
                    image[i][j].rgbtGreen = round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen
                                                   + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 4.0);
                }
                else
                {
                    image[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed
                                                 + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                    image[i][j].rgbtBlue = round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue
                                                  + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                    image[i][j].rgbtGreen = round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen
                                                   + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                }
            }
            // Last row
            else if (i == height - 1)
            {
                // Lower left corner
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                                                 + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0);
                    image[i][j].rgbtBlue = round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue
                                                  + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
                    image[i][j].rgbtGreen = round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen
                                                   + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) / 4.0);
                }
                // Lower right corner
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed
                                                 + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) / 4.0);
                    image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue
                                                  + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue) / 4.0);
                    image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen
                                                   + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen) / 4.0);
                }
                else
                {
                    image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                                                 + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) / 6.0);
                    image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue
                                                  + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) / 6.0);
                    image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen
                                                   + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) / 6.0);
                }
            }
            // left column
            else if (j == 0)
            {
                image[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                                             + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed
                                             + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue
                                              + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue
                                              + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen
                                               + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen
                                               + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
            }
            // Right column
            else if (j == width - 1)
            {
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed
                                             + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed
                                             + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) / 6.0);
                image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue
                                              + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue
                                              + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen
                                               + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen
                                               + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 6.0);
            }
            // 3x3 box
            else
            {
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                                             + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed
                                             + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0);
                image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue
                                              + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue
                                              + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 9.0);
                image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen
                                               + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen
                                               + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 9.0);
            }
        }
    }
    return;
}

// Makes array of Gx and Gy
void Gxy(int gx[3][3], int gy[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        gx[0][i] = i - 1;
        gx[1][i] = (i * 2) - 2;
        gx[2][i] = i - 1;
    }
    for (int i = 0; i < 3; i++)
    {
        gy[i][0] = i - 1;
        gy[i][1] = (i * 2) - 2;
        gy[i][2] = i - 1;
    }
}

// Limits the bytes to 255
int Limit(int byte)
{
    if (byte > 255)
    {
        byte = 255;
    }
    return byte;
}

// Gets final value of gx and gy;
int Finalg(int gx, int gy)
{
    int finalg = Limit(round(sqrt(pow(gx, 2) + pow(gy, 2))));
    return finalg;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Creates and allocates memory to gx and gy arrays
    int (*gy)[3] = calloc(3, 3 * sizeof(int));
    int (*gx)[3] = calloc(3, 3 * sizeof(int));
    Gxy(gx, gy);

    // Make copy of image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Variables in use
    int gx_sum_red, gx_sum_green, gx_sum_blue, gy_sum_red, gy_sum_green, gy_sum_blue, kernelrow, kernelcol, stat, finalg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initialize all variables to 0
            // kernelrow and kernelcol are counters to gx and gy arrays
            gy_sum_red = gy_sum_green = gy_sum_blue = gx_sum_red = gx_sum_green = gx_sum_blue = kernelrow = kernelcol = stat = 0;
            for (int rows = i - 1; rows <= i + 1; rows++)
            {
                for (int cols = j - 1; cols <= j + 1; cols++)
                {
                    // Gets the products' sum
                    if ((rows >= 0 && rows < height) && (cols >= 0 && cols < width))
                    {
                        // Sum with gx kernel
                        gx_sum_blue += copy[rows][cols].rgbtBlue * gx[kernelrow][kernelcol];
                        gx_sum_green += copy[rows][cols].rgbtGreen * gx[kernelrow][kernelcol];
                        gx_sum_red += copy[rows][cols].rgbtRed * gx[kernelrow][kernelcol];

                        // Sum with gy kernel
                        gy_sum_blue += copy[rows][cols].rgbtBlue * gy[kernelrow][kernelcol];
                        gy_sum_green += copy[rows][cols].rgbtGreen * gy[kernelrow][kernelcol];
                        gy_sum_red += copy[rows][cols].rgbtRed * gy[kernelrow][kernelcol];
                        kernelcol++;
                        stat++;
                    }
                    if (cols < 0)
                    {
                        kernelcol++;
                    }
                }
                kernelrow++;
                kernelcol = 0;
            }
            // Updates image with new values
            if (stat != 0)
            {
                image[i][j].rgbtBlue = Finalg(gx_sum_blue, gy_sum_blue);
                image[i][j].rgbtGreen = Finalg(gx_sum_green, gy_sum_green);
                image[i][j].rgbtRed = Finalg(gx_sum_red, gy_sum_red);
            }
            else
            {
                return;
            }
        }
    }
    return;
}

#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int height = 0;

    // Ask for height
    while (height < 1 || height > 8)
    {
        height = get_int("How tall the pyramid will be?: ");
    }

    for (int i = height; i > 0; i--)
    {
        for (int j = 1; j < height + 1; j++)
        {
            // Print spaces
            if (j < i)
            {
                printf(" ");
            }
            // Print #
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }

}
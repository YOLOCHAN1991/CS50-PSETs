#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;

    // Ask for height
    while (height < 1 || height > 100000)
    {
        height = get_int("How tall the pyramid will be?: ");
    }

    // Calling function
    void Pyramid(int height);
    Pyramid(height);
}

// Fucntion that creates pyramid
void Pyramid(int height)
{
    for (int i = height; i > 0; i--)
    {
        // Left side
        for (int j = 1; j < height + 1; j++)
        {
            if (j < i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf(" ");
        printf(" ");
        // Right side
        for (int j = height; j > 0 ; j--)
        {
            if (j >= i)
            {
                printf("#");
            }
        }

        printf("\n");
    }

}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

#define BLOCK 512

// Define BYTE
typedef uint8_t BYTE;

// Count of .jpg files
int jcount;

// Prototypes
bool Signaturecheck(BYTE block[BLOCK]);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open card.raw
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        fclose(raw);
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    // Declares variable to save current filename;
    char *jname = malloc(8 * sizeof(char));

    // Declare FILE to write jpg
    FILE *jpg;

    // Array that holds current block's data
    BYTE block[BLOCK];

    // Skips the header of the file
    while (fread(block, sizeof(BYTE), BLOCK, raw) == BLOCK)
    {
        if (Signaturecheck(block))
        {
            break;
        }
    }
    jcount = 0;
    sprintf(jname, "%03i.jpg", jcount);
    jpg = fopen(jname, "w");
    fwrite(block, 1, BLOCK, jpg);

    // Loop to Read raw and write on .jpgs
    while (fread(block, 1, BLOCK, raw) == BLOCK)
    {
        if (Signaturecheck(block))
        {
            fclose(jpg);
            jcount++;
            sprintf(jname, "%03i.jpg", jcount);
            jpg = fopen(jname, "w");
            fwrite(block, 1, BLOCK, jpg);
        }
        else
        {
            fwrite(block, 1, BLOCK, jpg);
        }
    }

    // Free allocated memory
    free(jname);

    // Close open file/s
    fclose(raw);
    fclose(jpg);

}

bool Signaturecheck(BYTE block[BLOCK])
{
    if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
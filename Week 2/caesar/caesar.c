#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string Encrypter(string plaintext, int key);

    // Error message if too many or no arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Checks if the argument is a value
    else
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                return 1;
            }
        }
    }

    int key = atoi(argv[1]);

    // User input and ciphertext output
    string plaintext = get_string("plaintext:  ");
    string ciphertext = Encrypter(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);

    return 0;

}

// Caesar encrypting method
string Encrypter(string plaintext, int key)
{
    string ciphertext = plaintext;
    int tempdec;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // Saves the ASCII value + key
        tempdec = plaintext[i] + key;

        if (isupper(plaintext[i]))
        {
            // Loop to get letter if value is bigger than Z
            while (tempdec > 90)
            {
                tempdec -= 26;
            }
            ciphertext[i] = tempdec;
        }
        else if (islower(plaintext[i]))
        {
            // Loop to get letter if value is bigger than z
            while (tempdec > 122)
            {
                tempdec -= 26;
            }
            ciphertext[i] = tempdec;
        }
    }
    return ciphertext;
}
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Functions' prototypes
    bool Inputline(int argc, string argv);
    string Encrypter(char lowerkey[], char upperkey[], string plaintext);

    // Variables
    char lowerkey[26];
    char upperkey[26];
    string plaintext;
    string ciphertext;

    // Checks for valid input
    bool errorcheck = Inputline(argc, argv[1]);
    if (errorcheck)
    {
        return 1;
    }

    // Makes two keys: one lowercase, one uppercase
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        lowerkey[i] = tolower(argv[1][i]);
        upperkey[i] = toupper(argv[1][i]);
    }


    plaintext = get_string("plaintext: ");
    //Encrypts text
    ciphertext = Encrypter(lowerkey, upperkey, plaintext);
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

// Checks for valid input
bool Inputline(int argc, string argv)
{
    // There is none or too many arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Argument doesn't have 26 letters
    else if (strlen(argv) != 26)
    {
        printf("Invalid key: Must be 26 characaters\n");
        return 1;
    }
    // Check for digits
    else
    {
        for (int i = 0, n = strlen(argv); i < n; i++)
        {
            if (isdigit(argv[i]))
            {
                printf("Invalid key: must have no digits\n");
                return 1;
            }

            for (int j = i + 1; j < n; j++)
            {
                if (argv[i] == argv[j])
                {
                    printf("Invalid key: must have no repeated letters\n");
                    return 1;
                }
            }
        }
        return 0;
    }
}

// Encrypts plaintext
string Encrypter(char lowerkey[], char upperkey[], string plaintext)
{
    string ciphertext = plaintext;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // Encrypts uppercase letters
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = upperkey[plaintext[i] - 65];
        }
        // Encrypts lowercase letters
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = lowerkey[plaintext[i] - 97];
        }
    }
    return ciphertext;
}
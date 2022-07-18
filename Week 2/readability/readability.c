#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Declaring variables
    int letters;
    int words;
    int sentences;
    int index;

    // Declaring function
    float Index(int letters, int sentences, int words);
    int count_letters(string text);
    int count_words(string text);
    int count_sentences(string text);


    string text = get_string("Text: \n");

    // Get the count of letters, words, and sentences
    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);


    // Float index = Index(letters, sentences, words);
    index = round(Index(letters, sentences, words));

    // Print result
    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Gets the index
float Index(int letters, int sentences, int words)
{
    float L = ((float)letters / words) * 100.00;
    float S = ((float)sentences / words) * 100.00;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return index;
}


int count_letters(string text)
{
    int letters = 0;

    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            letters++;
        }
    }
    printf("%i",letters);

    return letters;
}

int count_words(string text)
{
    int words = 0;

    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        if (text[i] == ' ' || text[i] == '\0')
        {
            words++;
        }
    }

    return words;
}

int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    return sentences;
}

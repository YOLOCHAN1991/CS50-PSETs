// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26 * 26;

// Word counter
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);
    node *temp = table[index];
    while (temp != NULL)
    {
        if (strcasecmp(word, temp->word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int len = strlen(word);
    // 1 letter
    if (len < 2)
    {
        return (676 * (toupper(word[0]) - 'A'));
    }
    // 2 letters
    else if (len < 3)
    {
        return (676 * (toupper(word[0]) - 'A'))
               + (isalpha(word[1]) ? (26 * (toupper(word[1]) - 'A')) : 0);
    }
    // 3 letters
    else if (len < 4)
    {
        return (676 * (toupper(word[0]) - 'A'))
               + (isalpha(word[1]) ? (26 * (toupper(word[1]) - 'A')) : 0)
               + (isalpha(word[2]) ? (toupper(word[2]) - 'A') : 0);
    }
    // 4 or more letters
    else
    {
        return (17576 * (toupper(word[0]) - 'A'))
               + (isalpha(word[1]) ? (676 * (toupper(word[1]) - 'A')) : 0)
               + (isalpha(word[2]) ? (26 * (toupper(word[2]) - 'A')) : 0)
               + (isalpha(word[3]) ? (toupper(word[3]) - 'A') : 0);
    }

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    if (dictionary == NULL)
    {
        return false;
    }

    // Open dictionary file
    FILE *ptr = fopen(dictionary, "r");
    if (ptr == NULL)
    {
        return false;
    }

    // Declare and initialize variables
    unsigned int index = 0;
    node *dword;
    char buffer[LENGTH + 1];
    while (fscanf(ptr, "%s", buffer) != EOF)
    {
        // Hash function
        index = hash(buffer);

        // Allocates memory for new node
        dword = malloc(sizeof(node));
        if (dword == NULL)
        {
            fclose(ptr);
            unload();
            return false;
        }

        // Copy word into node
        strcpy(dword->word, buffer);

        // loads word into hash table
        if (table[index] == NULL)
        {
            table[index] = dword;
            dword->next = NULL;
        }
        else
        {
            dword->next = table[index]->next;
            table[index]->next = dword;
        }

        word_count++;
    }

    // Close file
    fclose(ptr);
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return (&load) ? word_count : 0;
}

// Deletes hash row
void rowdeletion(node *hashrow)
{
    node *p = hashrow->next;
    while (p != NULL)
    {
        node *next = p->next;
        free(p);
        p = next;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            rowdeletion(table[i]);
            free(table[i]);
        }
    }
    return true;
}

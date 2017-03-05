/**
 * Implements a dictionary's functionality.
 */

//* Note: Hash table from Wikipedia - https://en.wikipedia.org/wiki/Hash_function
// ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dictionary.h"

// Set size of hashtable
#define SIZE 1000000

// Creat nodes for linked list
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
}
node;

// Create hashtable
node* hashtable[SIZE] = {NULL};

// Create hash function
int hash (const char* word)
{
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // if alpha character
        if(isalpha(word[i]))
            n = word[i] - 'a' + 1;
            
        // if comma
        else
            n = 27;
            
        hash = ((hash << 3) + n) % SIZE;
    }
    return hash;
}

// Create global variable to count size
int dictionarySize = 0;

// * Loads dictionary into memory. Returns true if successful else false.
// * Returns true if word is in dictionary else false.
 
bool load(const char* dictionary)
{
    // Opens dictionary
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
       return false;
       
   // Create an array for word to be stored
   char word[LENGTH+1];
   
   // Scan through file, loading each word into hash table
   while (fscanf(file, "%s\n", word) != EOF)
   {
        // Add to dictionary size
        dictionarySize++;
        
        // Allocate memory for new word
        node* newWord = malloc(sizeof(node));
        
        // Add word into new node
        strcpy(newWord->word, word);
        
        // ID what index for word
        int index = hash(word);
        
        // If hashtable is empty insert NULL
        if (hashtable[index] == NULL)
        {
            hashtable[index] = newWord;
            newWord->next = NULL;
        }
        else
        {
            newWord->next = hashtable[index];
            hashtable[index] = newWord;
        }
    }
    
    // Close dictionary file
    fclose(file);
    
    // Return true if success
    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // Creates temp variable to store lower-case word version
    char temp[LENGTH+1];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
        temp[i] = tolower(word[i]);
    temp[len] = '\0';
    
    // Calculate what index of array for word
    int index = hash(temp);
    
    // If hashtable is empty, return false
    if (hashtable[index] == NULL)
    {
        return false;
    }
    
    // Cursor to compare to word
    node* cursor = hashtable[index];
    
    // Iterate through table unless hashtable is NULL
    while (cursor != NULL)
    {
        if (strcmp(temp, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    
    // If word isn't found return false
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}

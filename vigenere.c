#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// prototypes
char encode(char src, char key);
bool is_letter(char src);
bool is_upper(char src);
bool is_lower(char src);
char up_case(char src);
char down_case(char src);
bool is_in_range(char src, char min, char max);
char rotate(char src, char anchor, char key, int range);

int main(int argc, string argv[])
{
    // wrong number of arguments
    if (argc != 2)
    {
        printf("Usage: caesar <key> \n");
        return 1;
    }

    string key = argv[argc - 1];
    int key_len = strlen(key);

    // verify all chars
    for (int i = 0; i < key_len; i++)
    {
        if (!is_upper(key[i]) && !is_lower(key[i]))
        {
            printf("Key must be all letters! \n");
            return 1;
        } 
    }

    string plain_text;
    int plain_len;
    
    // user inputs
    do
    {
        printf("Enter text to encrypt: ");
        plain_text = GetString();
        plain_len = strlen(plain_text);
    }
    while (plain_len == 0);
     
    printf("Rotate by key \"%s\": \n%s \n", key, plain_text);
   
    // begin processing
    for (int i = 0, key_space = 0; i < plain_len; i++)
    {
        char current = plain_text[i];
        char result;
        if(is_letter(current))
        {
            result = encode(current, key[key_space]);
            key_space = (key_space + 1) % key_len;
        }        
        else
        {
            result = current;
        }
        printf("%c", result);
    }
    printf("\n");
    // success
    return 0;
}

/*
 * Encode char if it's a letter, or return original
 */
char encode(char src, char key)
{
    //printf("key %s \n", key);
    if (is_upper(src))
    {
        return rotate(src, 'A', up_case(key), 26);
    }
    if (is_lower(src))
    {
        return rotate(src, 'a', down_case(key), 26);
    }
    else
    {
        return src;
    }
}

/*
 * Is char a letter
 */
bool is_letter(char src)
{
    return (is_upper(src) || is_lower(src));
}

/*
 * Is char an upper case letter
 */
bool is_upper(char src)
{
    return (is_in_range(src, 'A', 'Z'));
}

/*
 * return uppercase
 */

char up_case(char src)
{
    if (is_lower(src))
    {
        return src - ('a' - 'A');
    }
    else
    {
        return src;
    } 
}

/*
 * return lowercase
 */

char down_case(char src)
{
    if (is_upper(src))
    {
        return src + ('a' - 'A');
    }
    else
    {
        return src;
    } 
}

/*
 * Is char a lower case letter
 */
bool is_lower(char src)
{
    return (is_in_range(src, 'a', 'z')); 
}

/*
 * Is char between the other two chars, inclusive
 */
bool is_in_range(char src, char min, char max)
{
    return (src >= min && src <= max);
}

/*
 * Rotate char by key modulo a given anchor and range
 */
char rotate(char src, char anchor, char key, int range)
{
    //printf("src %c anchor %c key %c range %i \n", src, anchor, key, range);
    char result = (char) (anchor + (((src - anchor) + (key - anchor)) % range));
    //printf("result %c \n", result);
    return result;
}

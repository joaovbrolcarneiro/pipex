#include "pipex.h"

// Helper function to count the number of words separated by the delimiter.
static size_t count_words(const char *s, char c)
{
    size_t count = 0;
    while (*s)
    {
        while (*s == c)
            s++;
        if (*s)
        {
            count++;
            while (*s && *s != c)
                s++;
        }
    }
    return count;
}

// Helper function to duplicate a substring from start to end.
char *strdup_until(const char *start, const char *end)
{
    size_t len = end - start;
    char *str = malloc(len + 1);
    if (!str)
        return NULL;
    for (size_t i = 0; i < len; i++)
        str[i] = start[i];
    str[len] = '\0';
    return str;
}

// ft_split: Splits a string into an array of substrings based on the delimiter 'c'.
char **ft_split(char const *s, char c)
{
    if (!s)
        return NULL;

    size_t words = count_words(s, c);
    char **result = malloc((words + 1) * sizeof(char *));
    if (!result)
        return NULL;

    size_t i = 0;
    while (*s)
    {
        while (*s == c)
            s++;
        if (*s)
        {
            const char *start = s;
            while (*s && *s != c)
                s++;
            result[i] = strdup_until(start, s);
            if (!result[i])
            {
                // Free previously allocated memory on error
                for (size_t j = 0; j < i; j++)
                    free(result[j]);
                free(result);
                return NULL;
            }
            i++;
        }
    }
    result[i] = NULL;
    return result;
}
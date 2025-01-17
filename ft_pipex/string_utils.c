#include "pipex.h"

// Helper function to count the number of words separated by the delimiter.


char *join_paths(char *path, char *cmd)
{
    char *joined;
    size_t len1 = ft_strlen(path);
    size_t len2 = ft_strlen(cmd);

    joined = malloc(len1 + len2 + 2);  // 1 for '/' and 1 for null terminator
    if (!joined)
        return (NULL);

    ft_strncpy(joined, path, len1);  // Copy path to joined
    joined[len1] = '/';  // Add the '/' separator
    ft_strncpy(joined + len1 + 1, cmd, len2);  // Copy cmd to joined

    // Debugging print to check the joined path
    printf("Resolved command path: %s\n", joined);

    return (joined);
}


int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    if (n == 0)
        return (0);
    i = 0;
    while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if (i == n)
        return (0);
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


// ft_strlen: Returns the length of the string (excluding the null terminator).
size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

// ft_memcpy: Copies n bytes from memory area src to memory area dest.
void *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;
    
    while (n--)
        *d++ = *s++;
    
    return dest;
}

// ft_strcpy: Copies the string src (including the null terminator) to dest.
char *ft_strcpy(char *dest, const char *src)
{
    char *d = dest;
    while ((*d++ = *src++))
        ;
    return dest;
}
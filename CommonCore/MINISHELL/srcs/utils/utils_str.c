#include "../../headers/minishell.h"



int is_delimiter(char c, const char *delimiter)
{
    int i;

    i = 0;
    while (delimiter[i])
    {
        if (delimiter[i] == c)
            return (1);
        i++;
    }
    return (0);
}


int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
    if (*needle == '\0') // If the needle is empty, return the haystack
        return (char *)haystack;

    if (*haystack == '\0') // If haystack is empty, return NULL (no match)
        return NULL;

    const char *h = haystack;
    const char *n = needle;

    // Check if the current part of haystack matches the needle
    while (*h && *n && *h == *n)
    {
        h++;
        n++;
    }

    // If we've matched the entire needle, return the start of the match
    if (*n == '\0')
        return (char *)haystack;

    // Recur for the next character in the haystack
    return ft_strstr(haystack + 1, needle);
}

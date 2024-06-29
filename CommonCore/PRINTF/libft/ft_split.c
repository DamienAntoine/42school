/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:23:10 by dantoine          #+#    #+#             */
/*   Updated: 2024/02/22 12:39:00 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

static int	ft_allocate(char **tab, char const *s, char sep)
{
	int		count;
	char		**tab1;
	char const	*tmp;

	count = 0;
	tmp = s;
	tab1 = tab;
	while (*tmp)
	{
		while (*s == sep)
			++s;
		tmp = s;
		while (*tmp && *tmp != sep)
			++tmp;
		if (*tmp == sep || tmp > s)
		{
			*tab1 = ft_substr(s, 0, tmp - s);
			if (!*tab1)
			{
				free_tab(tab, count);
				return (0);
			}
			s = tmp;
			++tab1;
			++count;
		}
	}
	*tab1 = NULL;
	return (1);
}

static int	ft_count_words(char const *s, char sep)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == sep)
			++s;
		if (*s)
			++word_count;
		while (*s && *s != sep)
			++s;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		size;

	if (!s)
		return (NULL);
	size = ft_count_words(s, c);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	if (!ft_allocate(new, s, c))
		return (NULL);
	return (new);
}
/*
int main() {
    char str[] = "This is a sample string";
    char charset[] = " ";

    char **result = ft_split(str, charset);

    for (int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
        free(result[i]);  // Don't forget to free each word
    }

    free(result);  // Don't forget to free the array

    return 0;
}
*/

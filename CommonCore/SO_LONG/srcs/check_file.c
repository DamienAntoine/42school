#include "../headers/so_long.h"

static int	find(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (to_find[i])
	{
		if (to_find[i] != str[i])
			return (0);
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	check_file(char *line)
{
	while (*line)
	{
		if (*line == '.')
		{
			if (find(line, ".ber"))
			{
				return ;
			}
		}
		line++;
	}
	perror("ERROR: invalid map file");
	exit(1);
}
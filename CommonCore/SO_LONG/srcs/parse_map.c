#include "../headers/so_long.h"

int		map_height(char *map)
{
	int	i;

	while (map[i])
		i++;
	return (i);
}

char	**parse_map(char *map)
{
	char	*cur_line;
	char	*all_lines;
	int		fd;

	cur_line = "";
	all_lines = ft_strdup("");
	fd = open(map, O_RDONLY);
	if (fd < 0)
		perror("ERROR: Couldn't open fd in parse_map function");
	while (cur_line)
	{
		cur_line = get_next_line(fd);
		if (cur_line == NULL || cur_line[0] == '\n')
			break;
		all_lines = ft_strjoin(all_lines, cur_line);
		free(cur_line);
	}
	free(cur_line);
	close(fd);
	if (all_lines[0] == '\0')
		perror("ERROR: Selected map is NULL");
	return (ft_split(all_lines, '\n'));
}
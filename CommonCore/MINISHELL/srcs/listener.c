# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*
documentation :
https://harm-smits.github.io/42docs/projects/minishell
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
*/

typedef struct s_commands
{
	char		**cmds;
}				t_commands;

int	main(void)
{
	t_commands *commands;

	commands = NULL;
	while (1)
	{
		printf("$>");
		commands->cmds = get_next_line();
	}
}

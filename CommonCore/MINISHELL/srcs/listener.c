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

//infinite loop to listen for commands
//sends each command line to a function thatchecks the grammar and syntax
//separates each command into tokens

//each token are treated by a function that calls the operation related to the token

int	main(void)
{
	t_commands *commands;
    int loop;

    loop = 1;
	commands = NULL;
	while (loop)
	{
        loop = 0;
		printf("$>");
		commands->cmds = get_next_line();
        if ()
        {
            loop = 1;
            
        }
	}
}

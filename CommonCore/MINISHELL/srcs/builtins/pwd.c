#include "../../headers/minishell.h"
//syntax: pwd
//implemented with no options
//shows in which directory the shell is
/*void	ft_pwd(void)
{
	char	cwd[1024];
	printf("%s", getcwd(cwd, sizeof(cwd)));
}*/

//could also be:
void	ft_pwd(t_env *cur_env)
{
	while (ft_strcmp(cur_env->type, "PWD") != 0)
	{	
		//debug
	//	printf("env type: %s\n", cur_env->type);
		cur_env = cur_env->next;
	}
	//printf("found\n");
	ft_putstr_fd(cur_env->value, 1);
	ft_putchar_fd('\n', 1);
} //idk which is best

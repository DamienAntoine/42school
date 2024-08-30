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
		cur_env = cur_env->next;
	printf("%s", cur_env->value);
} //idk which is best

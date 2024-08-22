//syntax: pwd
//implemented with no options
//shows in which directory the shell is
void	pwd(void)
{
	char	cwd[1024];
	printf("%s", getcwd(cwd, sizeof(cwd)));
}

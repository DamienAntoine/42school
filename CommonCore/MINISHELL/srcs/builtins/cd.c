#include "../../headers/minishell.h"

char	*get_current_directory(void)
{
	return (getcwd(NULL, 0));
}

static int handle_home_directory(t_data *cur, char **target_dir, char *oldpwd)
{
    *target_dir = find_env_value(cur->env, "HOME");
    if (!*target_dir)
    {
        printf_and_free("Home directory not set\n", oldpwd);
        return 1;
    }
    return 0;
}

static int handle_oldpwd(t_data *cur, char **target_dir, char *oldpwd)
{
    char *oldpwd_env = find_env_value(cur->env, "OLDPWD");
    if (!oldpwd_env || ft_strlen(oldpwd_env) == 0)
    {
        printf_and_free("OLDPWD not set\n", oldpwd);
        return 1;
    }
    printf("%s\n", oldpwd_env);
    *target_dir = oldpwd_env;
    return 0;
}

static int handle_env_variable(t_data *cur, char **target_dir, char *oldpwd)
{
    *target_dir = find_env_value(cur->env, &cur->commands->args[0][1]);
    if (!*target_dir)
    {
        printf("cd: %s: No such environment variable\n",
            &cur->commands->args[0][1]);
        free(oldpwd);
        return 1;
    }
    return 0;
}

static int validate_arguments(t_data *cur, char *oldpwd)
{
    if (cur->commands->args[1])
    {
        errno = EINVAL;
        ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
        free(oldpwd);
        cur->state.last_exit_status = 1;
        return 1;
    }
    return 0;
}

static int change_directory(t_data *cur, const char *target_dir, char *oldpwd)
{
    if (chdir(target_dir) != 0)
    {
        perror_and_free("cd", oldpwd);
        cur->state.last_exit_status = 1;
        return 1;
    }
    return 0;
}

static void update_environment(t_data *cur, char *oldpwd, char *newpwd)
{
    update_or_add_env_variable(&cur->env, "OLDPWD", oldpwd);
    update_or_add_env_variable(&cur->env, "PWD", newpwd);
}

static char *get_target_dir(t_data *cur, char *oldpwd)
{
    char *target_dir;

    target_dir = NULL;
    if (!cur->commands->args[0])
    {
        if (handle_home_directory(cur, &target_dir, oldpwd))
            return NULL;
    }
    else if (!ft_strcmp(cur->commands->args[0], ".."))
        target_dir = "..";
    else if (!ft_strcmp(cur->commands->args[0], "-"))
    {
        if (handle_oldpwd(cur, &target_dir, oldpwd))
            return NULL;
    }
    else if (cur->commands->args[0][0] == '$')
    {
        if (handle_env_variable(cur, &target_dir, oldpwd))
            return NULL;
    }
    else
        target_dir = cur->commands->args[0];
    return target_dir;
}

int ft_cd(t_data *cur)
{
    char *oldpwd = get_current_directory();
    char *newpwd;
    char *target_dir;

    oldpwd = get_current_directory();
    if (!oldpwd)
    {
        perror("getcwd");
        return 1;
    }
    target_dir = get_target_dir(cur, oldpwd);
    if (validate_arguments(cur, oldpwd) || !target_dir)
        return 1;
    if (change_directory(cur, target_dir, oldpwd))
        return 1;
    newpwd = get_current_directory();
    if (!newpwd)
    {
        perror_and_free("getcwd", oldpwd);
        return 1;
    }
    update_environment(cur, oldpwd, newpwd);
    free(oldpwd);
    free(newpwd);
    return 0;
}

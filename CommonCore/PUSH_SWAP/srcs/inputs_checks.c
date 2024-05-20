int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}

int	ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

int	check_inputs(int argc, char **input)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		j = 0;
        while (input[i][j] != '\0')
        {
            if (!ft_isdigit(input[i][j]) && !ft_issign(input[i][j]))
                return (0);
            j++;
        }
		i++;
	}
	return (1);
}



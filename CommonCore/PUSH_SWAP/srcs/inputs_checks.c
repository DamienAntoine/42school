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

int	check_inputs(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isdigit(input[i] == 0))
			return (0);
		if (ft_issign(input[i] == 0))
			return (0);
	}
	return (1);
}



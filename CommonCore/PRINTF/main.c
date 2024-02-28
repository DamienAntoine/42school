#include <stdio.h>
#include "./includes/ft_printf.h"

int	main()
{
	int	integer = 50;
	char	letter = 'a';
	char	*str = "abcdef";
	int	*ptr = 65132;
	unsigned int	uint = 5500;
	ptr = (void *)ptr;

	ft_printf("test char %c\n test str %s\n test ptr %p\n test int %i, %d\n test unsigned %x, %X\n", letter, str, ptr, integer, integer, uint, uint);

	printf("test char %c\n test str %s\n test ptr %p\n test int %i, %d\n test unsigned %x, %X\n", letter, str, ptr, integer, integer, uint, uint);
		return 0;
}
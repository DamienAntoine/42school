#include <stdio.h>
#include "./includes/ft_printf.h"
#include "./includes/libft.h"

int	main()
{
	int	integer = 50;
	char	letter = 'a';
	char	*str = "abcdef";
	int	*ptr = 65132;
	unsigned int	uint = 5500;
	ptr = (void *)ptr;
	ft_printf("\nTEST 1:\n");
	ft_printf("*****FT_PRINTF*****\n");
	ft_printf("test char %c\ntest str %s\ntest ptr %p\ntest unsigned %u\ntest int %i, %d\ntest hexa %x, %X, %%\n\n", letter, str, ptr, uint, integer, integer, uint, uint);

	ft_printf("*****ST_PRINTF*****\n");
	printf("test char %c\ntest str %s\ntest ptr %p\ntest unsigned %u\ntest int %i, %d\ntest hexa %x, %X, %%\n\n", letter, str, ptr, uint, integer, integer, uint, uint);

	ft_printf("----------------------------\n\n");

	integer = -50;
	letter = 42;
	str = "yeah";
	ptr = "dfghhf";
	uint = -5500;
	ft_printf("TEST 2:\n");
	ft_printf("*****FT_PRINTF*****\n");
	ft_printf("test char %c\ntest str %s\ntest ptr %p\ntest unsigned %u\ntest int %i, %d\ntest hexa %x, %X, %%\n\n", letter, str, ptr, uint, integer, integer, uint, uint);

	ft_printf("*****ST_PRINTF*****\n");
	printf("test char %c\ntest str %s\ntest ptr %p\ntest unsigned %u\ntest int %i, %d\ntest hexa %x, %X, %%\n", letter, str, ptr, uint, integer, integer, uint, uint);
		return 0;
}
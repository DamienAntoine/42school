#include <stdio.h>

int	main()
{
	void *test = "abc123";
	printf("%p\n", test);

	int decimal = 10.15;
	printf("%.d\n", decimal);

	unsigned int usign = -5;
	printf("%u\n", usign);

	char *str = "";
	printf("%s\n", str);

	int hexa = -50;
	printf("%x", hexa);
	return 0;
}
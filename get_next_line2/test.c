#include <string.h>

void	strtest(char *buf)
{
	static char *curr;
	while (*buf)
	{
		
	}
}

void	funstr(char *str)
{
//	strcpy(str, "abc");
	str=  "abc";
}

void fun(int *i )
{
	(*i)++;
}

int main()
{
	int i;
	char *str;
	static int j;

	i = 1;
	j = 11;
	str = '0';
	fun(&i);
	fun(&i);
	fun(&i);
	funstr(&str);
	printf("%i %i %s:",i, j, &str);
}

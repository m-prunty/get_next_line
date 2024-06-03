#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"
#include <stdio.h>


int	main()
{
	int	fd[15];
	int i;
	int j;
	char *line;
	char *filelist[] = {"alternate_line_nl_no_nl","41_no_nl", "42_with_nl", 
		 "big_line_with_nl", "multiple_line_with_nl", "41_with_nl", "43_no_nl",
	     "alternate_line_nl_with_nl", "empty", "multiple_nlx5", "42_no_nl", "43_with_nl",
	     "big_line_no_nl", "multiple_line_no_nl", "nl"};
//	fd = open("file.txt", O_RDONLY);
	i = 0;
	while(i < 15)
	{
		fd[i] = open(filelist[i], O_RDONLY);
		//printf("\n%s", filelist[i]);
		i++;
	}
	i = 0;
	j = 0;

	while (i < 4)
	{
		j = 0;
		while (j < 3)
		{
			line = get_next_line(fd[j]);
			printf("\n%i %s", i, filelist[j]);
			printf("\na:%s;\n", line);
			free(line);
			j++;
		}
		i++;
	}
	return (0);
}

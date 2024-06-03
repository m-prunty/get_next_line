#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>


int	main()
{
	int	fd[15];
	int i;
	char *line;
	char *filelist[] = {"41_no_nl", "42_with_nl", "alternate_line_nl_no_nl",
		 "big_line_with_nl", "multiple_line_with_nl", "41_with_nl", "43_no_nl",
	     "alternate_line_nl_with_nl", "empty", "multiple_nlx5", "42_no_nl", "43_with_nl",
	     "big_line_no_nl", "multiple_line_no_nl", "nl"};
//	fd = open("file.txt", O_RDONLY);
	i = 0;
	while(i < 15)
	{
		fd[i] = open(filelist[i], O_RDONLY);
		printf("\n%s", filelist[i]);
		while ((line = get_next_line(fd[i])))
		{
			printf("\na:%s;", line);
			free(line);
		}
		i++;
	}
	return (0);
}

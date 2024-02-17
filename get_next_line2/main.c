int	main()
{
	int	fd;
	fd = open("file.txt", O_RDWR | O_APPEND);
	char *a = "a";
	while(a){
		a = get_next_line(fd);
		printf("\na: %s;", a);
	}
}

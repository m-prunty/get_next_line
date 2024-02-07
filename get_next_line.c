/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:49:42 by mprunty           #+#    #+#             */
/*   Updated: 2024/02/07 04:03:32 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>

char    *build_list(int fd, t_list **llist )
{
    int     n_rd;
    char    *nl_ptr;
    char    *buf;

    nl_ptr =  NULL;//list = head;
    while (!nl_ptr )
    {
        buf = malloc(sizeof(char) * BUFFER_SIZE + 1 );
		if (buf == NULL)
			return ;
        n_rd = read(fd, buf, BUFFER_SIZE);
		if (!n_read)
		{
			free(buf);
			return;
		}
        nl_ptr = ft_memchr(buf, BUFFER_SIZE);
        buf[n_rd ] = '\0';
        ft_lstadd_back(llist, ft_lstnew(buf));
    }
	return nl_ptr;
}
   


char    *get_next_line(int fd) 
{
    static t_list   *llist;
    char            *nl;
    char            *ret_str;
   
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);

    nl = build_list(fd, &llist);
	if (list == NULL)
		return (NULL);

    //ret_str = make_str(llist);
	//refresh_list(&llist, nl + 1); 
    return ret_str;
}


int main()
{
    int fd; 
    fd = open("file.txt", O_RDWR);
    char *a = "a";
    while(a){
        a = get_next_line(fd);
        printf("\na: %s;", a); 
    }   
}


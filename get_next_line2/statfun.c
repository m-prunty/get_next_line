/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:51:38 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/24 21:50:42 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

size_t  ft_strlen(const char *str)
{
	size_t  size;

	size = 0;
	while (*str++)
					size++;
	return (size);
}

char	*ft_strldup(const char *s, size_t size	)
{
	char	*s2;
	int	 n;
	int	 i;

	printf("%lu",size);
	i = 0;
	if (!n)
		return (NULL);
	s2 = malloc(size +1 * sizeof(const char));
	if (!s2)
		return (NULL);
	while (s[i]  && i<size)
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	printf(":%s:", s2);
	return (s2);
}

void	*ft_memchr(const void *buf,  size_t n )
{
	int c;

	c = '\n';
	while (n--)
	{
		if (*(char *)(buf) == (char)c)
			return ((void *)(buf));
		buf++;
	}
	return (0);
}

void	print_list(t_list *lst)
{
	int i;

	i = 0;
	while(lst->next)
	{
		i++;
		write(1,"\nstr-->",7);
		write(1, lst->str, BUFFER_SIZE);
		lst = lst->next;
	}
}

t_list  *ft_lstlast(t_list *lst)
{
	if (!lst)
		return NULL;
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int ft_lstsize(t_list *lst)
{
	int i;
	
	i = 1;
	if (!lst)
		return 0;
	while (lst->next)
	{   
		lst = lst->next;
		i++;
	}   
	return (i);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *)) 
{
		(*del)(lst->str);
		free(lst);
		lst = NULL;
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *tmp;

	if (lst)
	{   
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = tmp;
		}
	}   
}

void	ft_del(void *str)
{
	free(str);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list  *lastcur;

	if (lst && new)
	{   
		if (*lst)
		{
			lastcur = ft_lstlast(*lst);
			lastcur->next = new;
		}
		else
			*lst = new;
	}   
}

t_list	*ft_lstnew(void *str)
{
	t_list  *lst;

	lst = (t_list *)malloc(sizeof(*lst));
	lst->str = str;
	lst->next = NULL;
	return (lst);
}

char	*read_all(int fd, t_list **llist )
{
	int		n_rd;
	char	*nl_ptr;
	char	*buf;
	
	n_rd = BUFFER_SIZE + 1;
	nl_ptr =  NULL;//list = head;
	while (!nl_ptr && n_rd)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1 );
		n_rd = read(fd, buf, BUFFER_SIZE);
		nl_ptr = ft_memchr(buf, BUFFER_SIZE);
		buf[n_rd] = '\0';
		ft_lstadd_back(llist, ft_lstnew(buf));
	}
	if(nl_ptr ){
		ft_lstadd_back(llist, ft_lstnew(ft_strldup(buf,nl_ptr-buf)));}
	return nl_ptr;
}

char	*get_next_line(int fd)
{
	static t_list   *llist;
	char			*nl;
	char 			*nxtbuf;
	printf("\nNew iter\n");
	llist =NULL;
	nl = read_all(fd, &llist);
	print_list(llist);
	printf("\n:%i",ft_strlen(nl + 1));
	printf("\ns:%s", nl+1 );
	*llist->str = ft_strldup(nl + 1, ft_strlen(nl + 1));
}

int	main()
{
	int	fd;
	fd = open("file.txt", O_RDWR | O_APPEND);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
}

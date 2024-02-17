/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:51:38 by mprunty           #+#    #+#             */
/*   Updated: 2024/02/16 23:25:06 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

#include <stdio.h>

size_t  ft_strlen(const char *str)
{
	size_t  size;

	
	size = 0;
	if (*str)
		while (*str++)
					size++;
	return (size);
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
	
	printf("\nstr->:");
	while(lst->str )
	{
		i++;
		printf("%s:", lst->str);
		if (lst->next)
			lst = lst->next;
		else
			return ;
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

void
	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst->str);
		free(lst);
	}
}
void
	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst && (*lst)->str)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
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

t_list	*ft_lstnew(char *str)
{
	t_list  *lst;

	//if (*str)
	//{
		lst = (t_list *)malloc(sizeof(*lst));
		lst->str = str;
		lst->next = NULL;
		return (lst);
	//}
	//return NULL;
}

int ft_strlcpy(char *dst, const char *src, int size)
{
	int i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size < 0)
		size = (ft_strlen(src) - size);
	while (src[i] != '\0' && i < (size - 1)) 
	{   
		dst[i] = src[i];
		i++;
	}   
	dst[i] = '\0';
	return (ft_strlen(src));
}

int 	get_len_n(t_list *llist)
{
	int n;
	int	i;	
	
	if (!llist)
		return (0);
	n = 0;
	while (llist)
	{
		i = 0;
		while (llist->str[i])
		{
			if (llist->str[i] == '\n')
			{
				n++;
				return (n);
			}
			n++;
			i++;
		}
		llist = llist->next;
	}
	return (n);
}
void    dealloc(t_list **list, t_list *clean_node, char *buf)
{
    t_list  *tmp;

    if (NULL == *list)
        return ;
    while (*list)
    {   
        tmp = (*list)->next;
        free((*list)->str);
        free(*list);
        *list = tmp;
    }   
    *list = NULL;
    if (clean_node->str[0])
        *list = clean_node;
    else
    {   
        free(buf);
        free(clean_node);
    }   
}

void	refresh_list(t_list **llist)
{
	char	*nl_str;
	t_list	*lastcur;
	t_list	*nl_lst;
	int		i;
	int		j;

	lastcur = ft_lstlast(*llist);
	nl_str = malloc(BUFFER_SIZE +1  * sizeof(char));
	nl_lst = malloc(sizeof(t_list));

	i=0;
	j=0;
	while (lastcur->str[i] != '\n' && lastcur->str[i])// nl_str[i])
	{
//		printf("%c",lastcur->str[i]);
		i++;
	}
//	ft_strlcpy(nl_str, lastcur->str + i+1, BUFFER_SIZE );
	i++;
    while (lastcur->str[i] && lastcur->str[i])
        nl_str[j++] = lastcur->str[i++];
    nl_str[j] = '\0';
    //clean_node->str = nl_lst;
    //clean_node->next = NULL;

	nl_lst = ft_lstnew(nl_str);
	ft_lstclear(llist, free);
	dealloc(llist, nl_lst, nl_str); 
	//*llist = NULL;
	//if (nl_lst->str[0])
	//	*llist = nl_lst; 
	/*
	 else{
		free(nl_str);
		free(nl_lst);
	}
	*/
void	copy_str(t_list *llist, char *str)
{
	int i;
	int j;

	if (!llist)
		return ;
	j = 0;
	while (llist)
	{
		i = 0;
		while (llist->str[i])
		{
			if (llist->str[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = llist->str[i++];
		}
		llist = llist->next;
	}
	str[j] = '\0';
}

char	*make_str(t_list *llist)
{
	int	 str_len;
	char	*next_str;
	int 	i;

	i = 0;
	if (llist == NULL)
		return (NULL);
	str_len = get_len_n(llist);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);
	copy_str(llist, next_str);
	return (next_str);
}

void	build_list(int fd, t_list **llist )
{
	int		n_rd;
	char	*nl_ptr;
	char	*buf;
	
	n_rd = 1;
	nl_ptr =  NULL;
	buf = NULL;
	while (!nl_ptr)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1 );
		if (buf == NULL) 
			return ;
		n_rd = read(fd, buf, BUFFER_SIZE);
		if (!n_rd)
		{
			free(buf);
			return ;
		}

		nl_ptr = ft_memchr(buf, BUFFER_SIZE);
		buf[n_rd ] = '\0';
		ft_lstadd_back(llist, ft_lstnew(buf));
	}
	return ;
}

char	*get_next_line(int fd)
{
	static t_list   *llist = NULL;
	char 			*ret_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) <= 0 )
		return (NULL);
	build_list(fd, &llist);
	if (!llist)
		return (NULL);
	ret_str = make_str(llist);
	refresh_list(&llist);
	return ret_str;
}
 
int	main()
{
	int	fd;
	fd = open("file.txt", O_RDONLY);
	char *line;

	line = get_next_line(fd);
	while (line) {
		printf("\na: %s;", line);
		free(line);
		line = get_next_line(fd);
	}
	return 0;
}

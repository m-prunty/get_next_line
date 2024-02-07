/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:51:38 by mprunty           #+#    #+#             */
/*   Updated: 2024/01/30 17:43:07 by mprunty          ###   ########.fr       */
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

char	*ft_strldup(const char *s, int l)
{
	char	*s2;
	int	 n;
	int	 i;

	i = 0;
	n = ft_strlen(s) + 1;
	if (!n)
		return (NULL);
	s2 = malloc(n * sizeof(const char));
	if (!s2)
		return (NULL);
	while (s[i] && i < l)
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
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
	
	printf("\nstr->:");
	while(lst->next)
	{
		i++;
		printf("%s:", lst->str);
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

void	lstclear(t_list **lst)
{
	t_list *tmp;

	if (lst)
	{   
		while (*lst)
		{
			tmp = (*lst)->next;
	//		if ((*lst)->str){
	//			free((*lst)->str);
	//			(*lst)->str = '\0';
	//			}
			free(*lst);
			//(*lst) = NULL;
			(*lst) = tmp;
		}
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

	if (*str)
	{
		lst = (t_list *)malloc(sizeof(*lst));
		lst->str = str;
		lst->next = NULL;
		lst->s_len= 0;
		if (lst->str)
			lst->s_len = ft_strlen(str);
		return (lst);
	}
	return NULL;
}

char	*build_list(int fd, t_list **llist )
{
	int		n_rd;
	char	*nl_ptr;
	char	*buf;
	
	n_rd = -1;//BUFFER_SIZE + 1;
	nl_ptr =  NULL;//list = head;
	while (!nl_ptr && n_rd)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1 );
		n_rd = read(fd, buf, BUFFER_SIZE);
		
		nl_ptr = ft_memchr(buf, BUFFER_SIZE);
		buf[n_rd ] = '\0';
		ft_lstadd_back(llist, ft_lstnew(buf));
	}
	if(nl_ptr && n_rd > 0){
		//printf("%s",ft_strldup(buf,nl_ptr-buf));
		printf("\nnl-> %s, %i", nl_ptr+1, nl_ptr-buf );
		buf[nl_ptr-buf] = '\0';
		ft_lstadd_back(llist, ft_lstnew(buf));//ft_strldup(buf,BUFFER_SIZE - (nl_ptr-buf)+1)));
}
		//if (!nl_ptr)
		/*
		 * buf[n_rd + 1] = '\0';
		if(nl_ptr)
		{ 
			buf[nl_ptr - buf] = '\0';
			ft_lstadd_back(llist, ft_lstnew(buf));
			ft_strlcpy(buf, nl_ptr,(BUFFER_SIZE - (nl_ptr-buf)));
		}
		*/
	//	if(n_rd)
	//		ft_lstadd_back(llist, ft_lstnew(buf));
	//}
	//if(nl_ptr ){
	//	ft_strlcpy(buf, nl_ptr,(BUFFER_SIZE - (nl_ptr-buf)));
	//	ft_lstadd_back(llist, ft_lstnew(buf));}//ft_strldup(buf,nl_ptr-buf)));}
	return nl_ptr;
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

int 	get_len_n(t_list **llist)
{
	int 	n;
	t_list	*tmp;
	
	n = 0;
	tmp = *llist;
	while (tmp)
	{
		if (tmp->s_len)
			n = n +  (tmp)->s_len;
		tmp = (tmp)->next;
	}
	//printf("%i", n);
	return n;
}
char	*make_str(t_list *llist)
{
	int		n;
	char 	*ret_str;
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = llist;
	n = get_len_n(&tmp);
	ret_str = malloc((n * sizeof(char)) + 2);
	while (tmp)
	{
	//	if (tmp->str)
	//	{
			ft_strlcpy(ret_str + i, tmp->str, tmp->s_len + 1 );
			i = i+ tmp->s_len;
	//	}
	//	else{
	//		printf("b");
	//	}
		tmp = tmp->next;
	//	printf("%s", tmp->str);
	}

	ft_strlcpy(ret_str + i , "\n\0", 2);
	return ret_str;
}

void	refresh_list(t_list **llist, char *nl)
{
	char	*nl_str;
	int		n;

	n = ft_strlen(nl);
	nl_str = malloc((n + 1) * sizeof(char));
	if (n)
	{
	//if (!nl_str)
	//	= NULL;
		printf("\n nl:%s, %i ", nl, n);
	//if (nl)
		ft_strlcpy(nl_str, nl, BUFFER_SIZE);//, ft_strlen(nl));
	}	
	lstclear(llist);
	if (nl_str)
		*llist = ft_lstnew(nl_str);
}

char	*get_next_line(int fd)
{
	static t_list   *llist;
	char			*nl;
	char 			*ret_str;
	
	nl = build_list(fd, &llist);
//	print_list(llist);
	ret_str = make_str(llist);
	refresh_list(&llist, nl + 1);
	return ret_str;
}

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

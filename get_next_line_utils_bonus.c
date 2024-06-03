/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:10:57 by mprunty           #+#    #+#             */
/*   Updated: 2024/06/03 19:09:40 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"
/*
size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	if (*str)
		while (*str++)
			size++;
	return (size);
}
*/
int	nl_chr(const void *buf, size_t n)
{
	int		c;
	size_t	i;

	c = '\n';
	i = 0;
	while (i < n)
	{
		if (*(char *)(buf + i) == (char)c)
			return (i + 1);
		else
			i++;
	}
	return (0);
}

void	lstjoin(gnl_list **lst, char *str, int len, int has_nl)
{
	char	*tmptr;

	tmptr = malloc(len + (*lst)->s_len + 1 * sizeof(char));
	ft_strncpy(tmptr, (*lst)->str, (*lst)->s_len);
	ft_strncpy(tmptr + (*lst)->s_len, str, len);
	free((*lst)->str);
	(*lst)->str = tmptr;
	if (has_nl)
		(*lst)->nl += (*lst)->s_len + has_nl;
	(*lst)->s_len += len;
	return ;
}

gnl_list	*gnl_lstnew(char *str, int has_nl)
{
	gnl_list	*lst;

	lst = (gnl_list *)malloc(sizeof(*lst));
	lst->str = str;
	lst->next = NULL;
	lst->s_len = ft_strlen(lst->str);
	lst->nl = has_nl ;
	return (lst);
}

void	*ft_strncpy(void *dest, const void *src, size_t n)
{
	int	i;

	i = 0;
	while (i < (int)n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	((char *) dest)[i] = '\0';
	return (dest);
}

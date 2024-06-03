/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:51:38 by mprunty           #+#    #+#             */
/*   Updated: 2024/04/15 16:20:10 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

char	*get_next_str(gnl_list **lst)
{
	char	*ret_str;
	gnl_list	*tmp;

	ret_str = malloc(sizeof(char) * (*lst)->s_len + 1);
	ft_strncpy(ret_str, (*lst)->str, (*lst)->s_len);
	tmp = (*lst)->next;
	free((*lst)->str);
	(*lst)->str = NULL;
	free(*lst);
	*lst = tmp;
	return (ret_str);
}

void	lstadd_nl(gnl_list **lst, char *str, int has_nl)
{
	gnl_list	*lastcur;
	char	*m_str;
	int		len;

	len = ft_strlen(str);
	m_str = malloc(sizeof(char) * len + 1);
	ft_strncpy(m_str, str, len);
	if (lst && m_str)
	{
		if (*lst)
		{
			lastcur = *lst;
			while (lastcur->next)
				lastcur = lastcur->next;
			if (!lastcur->nl)
			{
				lstjoin(&lastcur, m_str, len, has_nl);
				free(m_str);
			}
			else
				lastcur->next = gnl_lstnew(m_str, has_nl);
		}
		else
			*lst = gnl_lstnew(m_str, has_nl);
	}
}

void	clean_buf(gnl_list **lst, char *buf)
{
	int		nl;
	char	*tmp;
	char	*newbuf;

	nl = nl_chr(buf, ft_strlen(buf));
	if (nl)
	{
		tmp = malloc(sizeof(char) * nl + 1);
		ft_strncpy(tmp, buf, nl);
		lstadd_nl(lst, tmp, nl);
		newbuf = buf + nl;
		if (ft_strlen(newbuf))
			clean_buf(lst, newbuf);
	}
	else
	{
		tmp = malloc(sizeof(char) * ft_strlen(buf) + 1);
		ft_strncpy(tmp, buf, ft_strlen(buf));
		lstadd_nl(lst, tmp, nl);
	}
	free(tmp);
	tmp = NULL;
	return ;
}

void	build_list(int fd, gnl_list **lst)
{
	int		n_rd;
	int		nl;
	char	*buf;

	n_rd = 0;
	nl = 0;
	buf = NULL;
	while (!nl)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		n_rd = read(fd, buf, BUFFER_SIZE);
		if (!n_rd)
		{
			free(buf);
			return ;
		}
		buf[n_rd] = '\0';
		clean_buf(lst, buf);
		nl = (*lst)->nl;
		free(buf);
	}
	return ;
}

char	*get_next_line(int fd)
{
	static gnl_list	*lst[FD_SIZE];
	char			*ret_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	build_list(fd, &lst[fd]);
	if (!lst[fd])
		return (NULL);
	ret_str = get_next_str(&lst[fd]);
	return (ret_str);
}

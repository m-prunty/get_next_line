/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:06:51 by mprunty           #+#    #+#             */
/*   Updated: 2024/12/26 23:02:14 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../include/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef FD_SIZE
#  define FD_SIZE 10 
# endif

# ifndef STRUCT_GNL_LIST
#  define STRUCT_GNL_LIST

typedef struct s_gnl_list
{
	struct s_gnl_list	*next;
	char				*str;
	int					s_len;
	int					nl;
}	t_gnl_list;
# endif

t_gnl_list	*gnl_lstnew(char *str, int has_nl);
int			nl_chr(const void *buf, size_t n);
void		lstjoin(t_gnl_list **lst, char *str, int len, int has_nl);
void		*ft_strncpy(void *dest, const void *src, size_t n);

void		lstadd_nl(t_gnl_list **lst, char *str, int has_nl);
char		*get_next_str(t_gnl_list **lst);
void		clean_buf(t_gnl_list **lst, char *buf);
void		build_list(int fd, t_gnl_list **lst);
char		*get_next_line(int fd);

#endif

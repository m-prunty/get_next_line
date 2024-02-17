/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 22:06:51 by mprunty           #+#    #+#             */
/*   Updated: 2024/02/11 06:00:53 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
	int				s_len;
	char			*nl;
}	t_list;

char	*get_next_line(int fd);

#endif

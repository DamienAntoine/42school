/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantoine <dantoine@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:35 by dantoine          #+#    #+#             */
/*   Updated: 2024/04/09 15:23:03 by dantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}		t_list;

int		scanline(t_list *list);
t_list	*ft_lstlast(t_list *lst);
char	*get_line(t_list *list);
void	struct_strcpy(t_list *list, char *str);
int		charcount(t_list *list);
void	cleanlist(t_list **list);
char	*get_next_line(int fd);
void	unmalloc(t_list **list, t_list *clean, char *buf);
void	create_lst(t_list **list, int fd);

#endif

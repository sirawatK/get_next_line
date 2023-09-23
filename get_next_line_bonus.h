/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikulnok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:10:21 by sikulnok          #+#    #+#             */
/*   Updated: 2023/09/22 22:10:23 by sikulnok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*str_buffer;
	struct s_list	*next;
}				t_list;
int		found_newline(t_list *lst);
void	my_append(t_list **lst, char *temp);
size_t	result_len(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst);
char	*get_next_line(int fd);

#endif

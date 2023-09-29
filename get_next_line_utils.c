/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikulnok <sikulnok@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:12:09 by sikulnok          #+#    #+#             */
/*   Updated: 2023/09/29 09:48:39 by sikulnok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *lst)
{
	int		i;
	t_list	*last_node;

	if (!lst)
		return (0);
	i = 0;
	last_node = ft_lstlast(lst);
	if (!last_node || !last_node->str_buffer)
		return (0);
	while (last_node->str_buffer[i])
	{
		if (last_node->str_buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	my_append(t_list **lst, char *buffer)
{
	t_list	*last_node;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
	{
		free(buffer);
		ft_lstclear(lst);
		return ;
	}
	new_node->str_buffer = buffer;
	new_node->next = NULL;
	if (!*lst)
	{
		*lst = new_node;
	}
	else
	{
		last_node = ft_lstlast(*lst);
		last_node->next = new_node;
	}
}

size_t	result_len(t_list *lst)
{
	size_t	len;
	int		i;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buffer[i])
		{
			if (lst->str_buffer[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		lst = lst->next;
	}
	return (len);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr;

	if (!lst)
		return (0);
	curr = lst;
	while (curr->next)
	{
		curr = curr->next;
	}
	return (curr);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->str_buffer);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

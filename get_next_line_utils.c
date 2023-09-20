/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikulnok <sikulnok@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:12:09 by sikulnok          #+#    #+#             */
/*   Updated: 2023/09/20 16:34:09 by sikulnok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->str_buffer[i])
		{
			if (lst->str_buffer[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}
/*
int	found_newline(t_list *lst)
{
	int		i;
	t_list	*last_node;

	i = 0;
	if (!lst || !(lst->str_buffer[0]))
		return (0);
	last_node = ft_lstlast(lst);
	if (!last_node)
		return (0);
	while (last_node->str_buffer[i] && last_node)
	{
		if (last_node->str_buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}*/

void	my_append(t_list **lst, char *temp)
{
	t_list	*last_node;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->str_buffer = temp;
	new_node->next = 0;
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

void	ft_lstclear(t_list **lst, char *new_buf)
{
	t_list	*temp;
	t_list	*new_node;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->str_buffer);
		free(*lst);
		*lst = temp;
	}
	*lst = 0;
	if (new_buf)
	{
		new_node = (t_list *)malloc(sizeof(size_t));
		if (!new_node)
			return ;
		new_node->str_buffer = new_buf;
		new_node->next = 0;
		*lst = new_node;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikulnok <sikulnok@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:28:25 by sikulnok          #+#    #+#             */
/*   Updated: 2023/09/29 09:56:33 by sikulnok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	creat_list(t_list **lst, int fd)
{
	int		byte_read;
	char	*buffer;

	while (!found_newline(*lst))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
		{
			ft_lstclear(lst);
			return ;
		}
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 1)
		{
			if (byte_read == -1)
				ft_lstclear(lst);
			free(buffer);
			return ;
		}
		buffer[byte_read] = '\0';
		my_append(lst, buffer);
	}
}

char	*get_result(t_list *lst)
{
	char	*result;
	int		i;
	int		j;

	result = (char *)malloc(sizeof(char) * (result_len(lst) + 1));
	if (!result)
		return (NULL);
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buffer[i])
		{
			if (lst->str_buffer[i] == '\n')
			{
				result[j++] = '\n';
				result[j] = '\0';
				break ;
			}
			result[j++] = lst->str_buffer[i++];
		}
		lst = lst->next;
	}
	result[j] = '\0';
	return (result);
}

int	clear_lst(t_list **lst, char *buffer)
{
	t_list	*new_head;

	ft_lstclear(lst);
	new_head = (t_list *)malloc(sizeof(t_list));
	if (!new_head)
	{
		free(buffer);
		return (0);
	}
	new_head->str_buffer = buffer;
	new_head->next = NULL;
	if (new_head->str_buffer[0])
	{
		*lst = new_head;
	}
	else
	{
		free(buffer);
		free(new_head);
	}
	return (1);
}

int	creat_new_head(t_list **lst)
{
	t_list	*last_node;
	char	*new_buf;
	int		i;
	int		j;

	if (!*lst)
		return (1);
	new_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new_buf)
	{
		ft_lstclear(lst);
		return (0);
	}
	last_node = ft_lstlast(*lst);
	i = 0;
	j = 0;
	while (last_node->str_buffer[i] != '\n' && last_node->str_buffer[i])
		i++;
	if (last_node->str_buffer[i] == '\n')
		i++;
	while (last_node->str_buffer[i])
		new_buf[j++] = last_node->str_buffer[i++];
	new_buf[j] = '\0';
	return (clear_lst(lst, new_buf));
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*result;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		ft_lstclear(&lst);
		return (NULL);
	}
	creat_list(&lst, fd);
	if (!lst)
		return (NULL);
	result = get_result(lst);
	if (!result)
	{
		ft_lstclear(&lst);
		return (NULL);
	}
	if (!creat_new_head(&lst))
	{
		free(result);
		return (NULL);
	}
	return (result);
}

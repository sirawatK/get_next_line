/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikulnok <sikulnok@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:28:25 by sikulnok          #+#    #+#             */
/*   Updated: 2023/09/20 16:40:24 by sikulnok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	creat_list(t_list **lst, int fd)
{
	int		is_end;
	char	*buffer;

	while (!found_newline(*lst))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		is_end = read(fd, buffer, BUFFER_SIZE);
		if (!is_end)
		{
			free(buffer);
			return ;
		}
		buffer[BUFFER_SIZE] = '\0';
		my_append(lst, buffer);
	}
}

char	*get_result(t_list *lst)
{
	size_t	res_len;
	char	*result;
	int		i;
	int		j;

	res_len = result_len(lst);
	result = (char *)malloc(sizeof(char) * (res_len + 1));
	if (!result)
		return (0);
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
	return (result);
}

int	clear_nextcall(t_list **lst)
{
	t_list	*last_node;
	char	*new_buf;
	int		i;
	int		j;

	if(!lst || !*lst)
		return (0);
	last_node = ft_lstlast(*lst);
	new_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new_buf)
		return (0);
	i = 0;
	j = 0;
	while (last_node->str_buffer[i] != '\n' && last_node->str_buffer[i])
		i++;
	/*if (!(last_node->str_buffer[i]))
		i = 0;*/
	if (last_node->str_buffer[i] == '\n')
		i++;
	while (last_node->str_buffer[i])
		new_buf[j++] = last_node->str_buffer[i++];
	new_buf[j] = '\0';
	ft_lstclear(lst, new_buf);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*result;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	creat_list(&lst, fd);
	result = get_result(lst);
	if (!result)
		return (0);
	clear_nextcall(&lst);
	return (result);
}
/*
#include <fcntl.h>
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *s;
	for(int i=0;i<8;i++)
	{
		s = get_next_line(fd);
		printf("___%s",s);
	}
	close(fd);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:10:45 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/25 19:28:41 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_realloc_byte(char *old, char c)
{
	size_t	i;
	char	*new;

	i = 0;
	while (old && old[i])
		i++;
	new = malloc((i + 2) * sizeof(*new));
	if (! new)
		return (NULL);
	if (old)
	{
		i = 0;
		while (old[i])
		{
			new[i] = old[i];
			i++;
		}
		free(old);
	}
	new[i] = c;
	new[i + 1] = 0;
	return (new);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	buf[BUFFER_SIZE];
	size_t	size;
	size_t	i;

	line = NULL;
	size = 1;
	while (size)
	{
		size = read(fd, buf, BUFFER_SIZE);
		i = 0;
		while (buf[i] && buf[i] != '\n')
		{
			line = ft_realloc_byte(line, buf[i]);
			i++;
		}
		if (buf[i] == '\n')
		{
			line = ft_realloc_byte(line, '\n');
			break ;
		}
	}
	return (line);
}

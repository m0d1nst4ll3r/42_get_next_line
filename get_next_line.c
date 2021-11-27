/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:10:45 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/27 05:10:45 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* -----------------------------------------------------------------------
**		ft_realloc_byte
**
**	Duplicates a string with enough space for an additional character
**		before freeing the old string and returning the new one.
**
**	Can be used with a NULL pointer to simply malloc a single-character
**		string, to start the chain.
**
**	This is used to effortlessly fill the line byte per byte
**		regardless of buffer size.
**
**	This isn't optimized and will become really slow for really long lines.
**
**	- old		old string to carry over
**	- c			character to add to the new string
** -------------------------------------------------------------------- */
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

/* -----------------------------------------------------------------------
**		parse_buffer
**
**	Parses the file descriptor's buffer to its end (symbolized by
**		data->size), reallocating and filling the line as it goes.
**
**	Stops at the first newline encountered and returns 1.
**
**	Returns 0 if no newline is encountered, in which case this function
**		will be called again with a new buffer,
**	or, if we've reached the end of the file, the data element
**		will be removed from the list of file descriptors.
**
**	- data		list's element corresponding to the current file descriptor
**	- line		string to be filled with the buffer's content
** -------------------------------------------------------------------- */
static int	parse_buffer(t_listfd *data, char **line)
{
	while (data->index < data->size && data->buffer[data->index] != '\n')
	{
		*line = ft_realloc_byte(*line, data->buffer[data->index]);
		if (! *line)
			return (1);
		data->index++;
	}
	if (data->index < data->size && data->buffer[data->index] == '\n')
	{
		*line = ft_realloc_byte(*line, '\n');
		data->index++;
		return (1);
	}
	return (0);
}

/* -----------------------------------------------------------------------
 **		get_next_line
 **
 **	Returns the next line it can read in the file described by fd.
 **	Returns NULL in case there is no next line.
 **	The line-ending '\n' is included in the returned string.
 **
 **	Multiple file descriptors can be used interchangeably.
 **
 **	The functions work by manipulating a list containing an entry
 **		for each file descriptor opened so far.
 **	Each new file descriptor will be assigned an element in the list,
 **		which will contain all its relevant data such as its buffer.
 **
 **	A file descriptor will be freed and removed from the list when we've
 **		returned the last line in the file.
 **
 **	- fd		file descriptor to read from
 ** -------------------------------------------------------------------- */
char	*get_next_line(int fd)
{
	static t_listfd	*listfd = NULL;
	t_listfd		*data;
	char			*line;

	if (! gnl_lstseek(listfd, fd))
		gnl_lstadd(&listfd, fd);
	data = gnl_lstseek(listfd, fd);
	if (data->index == data->size)
	{
		data->size = read(data->fd, data->buffer, BUFFER_SIZE);
		data->index = 0;
	}
	line = NULL;
	while (data->size)
	{
		if (parse_buffer(data, &line))
			return (line);
		data->size = read(data->fd, data->buffer, BUFFER_SIZE);
		data->index = 0;
	}
	gnl_lstdel(&listfd, data);
	return (line);
}

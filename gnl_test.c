/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 03:53:34 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/27 06:26:55 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static void	read_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line)
	{
		printf("%s", line);
		free(line);
	}
}

static void	read_file(int fd)
{
	char	*line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
}

int	main()
{
	int		fd1 = open("get_next_line.c", O_RDONLY);
	int		fd2 = open("get_next_line_utils.c", O_RDONLY);
	int		fd3 = open("get_next_line.h", O_RDONLY);

	read_line(fd1);
	read_line(fd2);
	read_line(fd3);
	read_line(fd1);
	read_line(fd1);
	read_line(fd1);
	read_line(fd2);
	read_line(fd2);
	read_line(fd2);
	read_line(fd2);
	read_file(fd1);
	read_file(fd2);
	read_file(fd3);
}

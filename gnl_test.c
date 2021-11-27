/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 03:53:34 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/27 18:16:09 by rpohlen          ###   ########.fr       */
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

int	main(int ac, char **av)
{
	(void)ac;
	int		fd1 = open(av[1], O_RDONLY);
	//int		fd2 = open(av[2], O_RDONLY);
	//int		fd3 = open(av[3], O_RDONLY);

	read_file(fd1);
}

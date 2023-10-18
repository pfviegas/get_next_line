/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:58:56 by pviegas           #+#    #+#             */
/*   Updated: 2023/05/23 10:34:21 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

static char	*chk_line(char *line, int bytes)
{
	if (bytes == 0 && *line == '\0')
	{
		free(line);
		return (NULL);
	}
	if (line == NULL)
	{
		line = malloc(1);
		if (line == NULL)
			return (NULL);
		*line = '\0';
	}
	return (line);
}

static char	*read_line(int fd, char *line)
{
	char	*str;
	int		bytes_read;

	str = (char *)malloc(BUFFER_SIZE + 1);
	if (str == NULL)
		return (0);
	bytes_read = 1;
	line = chk_line(line, bytes_read);
	while (!ft_strchr(line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, str, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(str);
			free(line);
			return (0);
		}
		str[bytes_read] = '\0';
		line = ft_strjoin(line, str);
	}
	free(str);
	line = chk_line(line, bytes_read);
	return (line);
}

static char	*ft_next_line(char *line)
{
	char	*str;
	char	*str_f;
	int		nl_pos;

	if (!ft_strchr(line, '\n'))
		str_f = line + (ft_strlen(line) - 1);
	else
		str_f = ft_strchr(line, '\n');
	nl_pos = str_f - line + 1;
	str = (char *)malloc(nl_pos + 1);
	if (str == NULL)
	{
		free(line);
		free(str);
		return (0);
	}
	ft_memmove(str, line, nl_pos);
	str[nl_pos] = '\0';
	ft_memmove(line, nl_pos + line, ft_strlen(line) - nl_pos + 1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, line);
	if (!line)
	{
		return (NULL);
	}
	next_line = ft_next_line(line);
	return (next_line);
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("./test_files/test_0.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open file.\n");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
*/
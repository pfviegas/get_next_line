/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:58:56 by pviegas           #+#    #+#             */
/*   Updated: 2023/05/23 10:36:24 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

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
	static char	*line[1024];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = read_line(fd, line[fd]);
	if (!line[fd])
	{
		return (NULL);
	}
	next_line = ft_next_line(line[fd]);
	return (next_line);
}

/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;

	fd1 = open("test_files/test_0.txt", O_RDONLY);
	fd2 = open("test_files/test_1.txt", O_RDONLY);
	fd3 = open("test_files/test_2.txt", O_RDONLY);
	fd4 = open("test_files/test_3.txt", O_RDONLY);
	i = 1;
	while (i < 17)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd4);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	return (0);
}
*/
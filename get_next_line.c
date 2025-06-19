/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:28:13 by miwehbe           #+#    #+#             */
/*   Updated: 2025/06/19 07:40:34 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include<stdio.h>

char	*_fill_line_buffer(int fd, char *left_c, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	if (!buffer)
		return (NULL);
	if (!left_c)
		left_c = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(left_c, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(left_c);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = left_c;
		left_c = ft_strjoin(left_c, buffer);
		free(tmp);
	}
	free(buffer);
	return (left_c);
}

char	*_set_line(char *line_buffer)
{
	size_t	i;

	i = 0;
	if (!line_buffer || line_buffer[0] == '\0')
		return (NULL);
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\n')
		i++;
	return (ft_substr(line_buffer, 0, i));
}

char	*update_leftover(char *line_buffer)
{
	size_t	i;
	char	*new_left;

	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	if (!line_buffer[i])
	{
		free(line_buffer);
		return (NULL);
	}
	new_left = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i - 1);
	free(line_buffer);
	return (new_left);
}

char	*get_next_line(int fd)
{
	static char	*left_c;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	left_c = _fill_line_buffer(fd, left_c, buffer);
	if (!left_c)
		return (NULL);
	line = _set_line(left_c);
	left_c = update_leftover(left_c);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
  if (fd == -1)
  {
	 perror("Error opening file");
	 return (1);
  }
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
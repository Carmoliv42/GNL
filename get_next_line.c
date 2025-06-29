/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:10:16 by carmoliv          #+#    #+#             */
/*   Updated: 2025/06/29 17:32:26 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_next_line(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (free(buffer), NULL);
	bytes = 1;
	while (!gnl_strchr(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
			return (free(temp), free(buffer), NULL);
		temp[bytes] = '\0';
		buffer = gnl_strjoin_free(buffer, temp);
		if (!buffer)
			return (free(temp), free(buffer), NULL);
	}
	free(temp);
	if (bytes <= 0 && (!buffer || buffer[0] == '\0'))
		return (free(buffer), NULL);
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	size_t	i;
	size_t	len;
	char	*line;

	if (!buffer || !buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	len = i;
	if (buffer[i] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*remove_line(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	i++;
	if (buffer[i] == '\0')
		return (free(buffer), NULL);
	new_buffer = malloc(gnl_strlen(buffer + i) + 1);
	if (!new_buffer)
		return (free(buffer), NULL);
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_next_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = remove_line(buffer);
	if (!buffer)
		buffer = NULL;
	return (line);
}

/* #include <stdio.h>
int	main(void)
{
	int	fd = open("1_char.txt", O_RDONLY);
	char *line;
	if(fd < 0)
		return (1);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
} */
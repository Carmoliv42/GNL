/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:10:16 by carmoliv          #+#    #+#             */
/*   Updated: 2025/06/26 22:29:05 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_next_line(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes;

	buffer = buffer_start(buffer);
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	bytes = 1;
	while (!gnl_strchr(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
			break ;
		temp[bytes] = '\0';
		buffer = gnl_strjoin_free(buffer, temp);
		if (!buffer)
			break ;
	}
	free(temp);
	if (bytes == -1)
		return (free(buffer), NULL);
	if (bytes == 0 && buffer[0] == '\0')
		return (free(buffer), NULL);
	return (buffer);
}

char	*extract_line(const char *buffer)
{
	size_t	i;
	char	*line;

	if (!buffer || !buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*remove_line(char *buffer)
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
	new_buffer = malloc(gnl_strlen(buffer + i + 1) + 1);
	if (!new_buffer)
		return (free(buffer), NULL);
	i++;
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
	char			*new_buffer;

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
	new_buffer = remove_line(buffer);
	if (!new_buffer)
		buffer = NULL;
	else
		buffer = new_buffer;
	return (line);
}

/* int	main(void)
{
	int	fd = open("test2.txt", O_RDONLY);
	char *line;
	//printf("%d", fd);
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
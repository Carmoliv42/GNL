/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:10:16 by carmoliv          #+#    #+#             */
/*   Updated: 2025/06/24 21:03:15 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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

int	main(void)
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
}
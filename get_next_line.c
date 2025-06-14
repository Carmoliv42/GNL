/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:10:16 by carmoliv          #+#    #+#             */
/*   Updated: 2025/06/14 19:54:55 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*remove_line(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while (buffer [i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(gnl_strlen(buffer + i + 1) + 1);
	if (!new_buffer)
		return (NULL);
	i++;
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
	buffer = remove_line(buffer);
	return (line);
}
/* 
int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	char *line;

	if(fd< 0)
		reutnr (1);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
} */
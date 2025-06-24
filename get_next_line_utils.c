/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:43:41 by carmoliv          #+#    #+#             */
/*   Updated: 2025/06/24 21:14:23 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_strchr(const char *str, int c)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != (char) c)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&str[i]);
}

char	*gnl_strjoin_free(char *line, const char *buffer)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len1;

	i = 0;
	j = 0;
	len1 = 0;
	if (!buffer && !line)
		return (NULL);
	if (line)
		len1 = gnl_strlen(line);
	result = malloc(len1 + gnl_strlen(buffer) + 1);
	if (!result)
		return (free(line), NULL);
	while (line && line[i])
	{
		result[i] = line[i];
		i++;
	}
	while (buffer && buffer[j])
		result[i++] = buffer[j++];
	result[i] = '\0';
	free(line);
	return (result);
}

static char	*buffer_start(char *buffer)
{
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	return (buffer);
}

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

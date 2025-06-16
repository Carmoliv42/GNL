/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:43:41 by carmoliv          #+#    #+#             */
/*   Updated: 2025/06/14 19:53:03 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char) c)
		return ((char *)&str[i]);
	return (NULL);
}

char	*gnl_strjoin_free(const char *line, const char *buffer)
{
	char	*result;
	int		i;
	int		j;
	size_t	total;

	i = 0;
	j = 0;
	if (!line || !buffer)
		return (NULL);
	total = gnl_strlen(line) + gnl_strlen(buffer);
	result = malloc(total + 1);
	if (!result)
		return (NULL);
	while (line[i])
	{
		result[i] = line[i];
		i++;
	}
	while (buffer[j])
		result[i++] = buffer[j++];
	result[i] = '\0';
	free((char *) line);
	return (result);
}

char	*read_next_line(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	bytes = 1;
	while ((!buffer ||!gnl_strchr(buffer, '\n')) && bytes > 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free (temp);
			free(buffer);
			return (NULL);
		}
		temp[bytes] = '\0';
		buffer = gnl_strjoin_free(buffer, temp);
	}
	free(temp);
	return (buffer);
}

char	*extract_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = malloc(i + 2);
	else
		line = malloc(i + 1);
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

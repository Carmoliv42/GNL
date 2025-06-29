/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:43:41 by carmoliv          #+#    #+#             */
/*   Updated: 2025/06/29 16:55:49 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *str, int c)
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

char	*gnl_strjoin_free(char *line, char *buffer)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len1;

	i = 0;
	j = 0;
	len1 = 0;
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

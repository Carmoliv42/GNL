/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:13:32 by carmoliv          #+#    #+#             */
/*   Updated: 2025/06/14 19:26:24 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#	define BUFFER_SIZE 42
# endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd);
char	*gnl_strchr(const char *str, int c);
char	*gnl_strjoin_free(char *line, const char *buffer);
size_t	gnl_strlen(const char *s);
char	*read_next_line(int fd, char *buffer);
char	*extract_line(char *buffer);

#endif
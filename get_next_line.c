/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znicola <znicola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:59:14 by znicola           #+#    #+#             */
/*   Updated: 2024/10/14 23:42:23 by znicola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //REMOVE after test

static char	*extend_malloc(char *ptr, size_t len, size_t new_len)
{
	char	*new_ptr;

	if (ptr == NULL)
	{
		new_ptr = malloc(new_len);
		if (!new_ptr)
			return (NULL);
		new_ptr[0] = '\0';
		return (new_ptr);
	}
	new_ptr = malloc(new_len);
	if (!new_ptr)
		return (NULL);
	ft_memset(new_ptr, 0, new_len);
	ft_memcpy(new_ptr, ptr, len);
	free(ptr);
	return (new_ptr);
}

static size_t	line_init(char **data, char **str)
{
	size_t	data_len;

	if (*data)
	{
		data_len = ft_strlen(*data);
		*str = extend_malloc(*str, 0, data_len + 1);
		if (!*str)
			return (0);
		ft_memset(*str, 0, data_len + 1);
		ft_strlcat(*str, *data, data_len + 1);
		free(*data);
		*data = NULL;
	}
	else
	{
		*str = NULL;
		return (0);
	}
	return (data_len);
}

static size_t	strlenchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ((unsigned char)c == str[i])
			return (i + 1);
		i++;
	}
	return (i);
}

static int	check_eol(char **data, char *buffer, ssize_t bytes_read)
{
	ssize_t	i;
	ssize_t	remaining_length;

	i = 0;
	while (buffer[i] != '\n' && i < bytes_read)
		i++;
	if (buffer[i] == '\n')
	{
		remaining_length = bytes_read - i - 1;
		if (remaining_length > 0)
		{
			*data = malloc(remaining_length + 1);
			if (!*data)
				return (-1);
			ft_memcpy(*data, &buffer[i + 1], remaining_length);
			(*data)[remaining_length] = '\0';
		}
		else
			*data = NULL;
		buffer[i + 1] = '\0';
		printf("here");
		return (1);
	}
	*data = NULL;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*data;
	ssize_t		bytes_read;
	char		buffer[BUFFER_SIZE + 1];
	char		*str;
	size_t		len;

	str = NULL;
	len = line_init(&data, &str);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	printf("bytes_read preloop: %ld\n", bytes_read);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (check_eol(&data, buffer, bytes_read) == 1)
			bytes_read = strlenchr(buffer, '\n');
		printf("bytes_read: %ld\n", bytes_read);
		str = extend_malloc(str, len, len + bytes_read + 1);
		if (!str)
			return (NULL);
		ft_strlcat(str, buffer, len + bytes_read + 1);
		if (bytes_read < BUFFER_SIZE || buffer[bytes_read - 1] == '\n')
			break ;
		len += bytes_read;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	printf("data postloop: %s\n", data);
	return (str);
}

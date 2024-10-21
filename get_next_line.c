/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znicola <znicola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:59:14 by znicola           #+#    #+#             */
/*   Updated: 2024/10/21 13:15:30 by znicola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*extend_malloc(char *ptr, size_t len, size_t new_len)
{
	char	*new_ptr;

	if (ptr == NULL)
	{
		new_ptr = malloc(new_len + 1);
		if (!new_ptr)
			return (NULL);
		new_ptr[0] = '\0';
		return (new_ptr);
	}
	new_ptr = malloc(new_len + 1);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, len);
	free(ptr);
	ptr = NULL;
	new_ptr[len] = '\0';
	return (new_ptr);
}

static char	*check_eol(char **data)
{
	char	*eol;
	char	*line;
	char	*new_data;

	eol = ft_strchr(*data, '\n');
	if (eol)
	{
		line = ft_strndup(*data, eol - *data + 1);
		new_data = ft_strndup(eol + 1, ft_strlen(eol + 1));
		if (!line || !new_data)
			return (NULL);
		free(*data);
		*data = new_data;
		return (line);
	}
	else if (*data && **data != '\0')
	{
		line = ft_strndup(*data, ft_strlen(*data));
		if (!line)
			return (NULL);
		free(*data);
		*data = NULL;
		return (line);
	}
	return (NULL);
}

static void	free_data(char **data, char *str, char *buffer, int fcase)
{
	if (fcase == 0)
		return ;
	if (fcase == -1)
	{
		free(buffer);
		buffer = NULL;
		free(*data);
		*data = NULL;
	}
	if (fcase == -2)
	{
		free(buffer);
		buffer = NULL;
	}
	if (fcase == 1)
	{
		free(buffer);
		buffer = NULL;
		if (!str && *data)
		{
			free(*data);
			*data = NULL;
		}
	}
}

static int	read_line(int fd, char *buffer, char **data)
{
	ssize_t	bytes_read;
	size_t	len;

	len = 0;
	if (*data != NULL)
		len = ft_strlen(*data);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (-1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		*data = extend_malloc(*data, len, len + bytes_read);
		if (!*data)
			return (-2);
		ft_strlcat(*data, buffer, len + bytes_read + 1);
		len += bytes_read;
		if (ft_strchr(*data, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*data;
	char		*buffer;
	char		*str;
	int			check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	check = read_line(fd, buffer, &data);
	free_data(&data, str, buffer, check);
	if (check < 0)
		return (NULL);
	if (data)
		str = check_eol(&data);
	free_data(&data, str, buffer, 1);
	if (data && !str)
		return (NULL);
	return (str);
}

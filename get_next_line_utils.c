/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znicola <znicola@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:43:38 by znicola           #+#    #+#             */
/*   Updated: 2024/10/14 20:02:48 by znicola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destptr;
	const unsigned char	*srcptr;

	if (!dest && !src)
		return (NULL);
	destptr = (unsigned char *)dest;
	srcptr = (const unsigned char *)src;
	while (n--)
	{
		*destptr = *srcptr;
		destptr++;
		srcptr++;
	}
	return (dest);
}

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (dest_len >= n)
		return (n + src_len);
	i = 0;
	while (src[i] && (dest_len + i) < (n - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	value;
	size_t			i;

	ptr = (unsigned char *)s;
	value = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		*ptr = value;
		ptr++;
		i++;
	}
	return (s);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char)c == *s)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

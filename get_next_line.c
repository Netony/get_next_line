/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:39:15 by dajeon            #+#    #+#             */
/*   Updated: 2023/01/11 16:38:05 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *s1);

char	*get_next_line(int fd)
{
	static char	*get_next_line;
	char		buf[BUFFER_SIZE];
	char		*ret;
	int			buf_max;
	size_t		size;

	while (1)
	{
		buf_max = read(fd, buf, BUFFER_SIZE);
		if (buf_max == 0)
		{
			ret = get_next_line;
			free(get_next_line);
			break ;
		}
		else if (buf_max == -1)
		{
			free(get_next_line);
			return (NULL);
		}
		size = ft_memchr_size(buf, '\n', buf_max);
		if (size)
		{
			ret = ft_append_nsize(get_next_line, buf, size);
			get_next_line = ft_append_nsize(NULL, buf + size, buf_max - size);
			break ;
		}
		else
			get_next_line = ft_append_nsize(get_next_line, buf, buf_max);
	}
	return (ret);
}

size_t	ft_memchr_size(const void *m, int c, size_t n)
{
	size_t	size;
	char	*s;

	s = (char *)m;
	size = 0;
	while (size < n)
	{
		if (s[size] == (char)c)
			return (size + 1);
		size++;
	}
	return (0);
}

char	*ft_append_nsize(char *s1, const char *s2, size_t n)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*append;

	len = ft_strlen(s1);
	append = (char *)malloc(sizeof(char) * (1 + len + n));
	if (append)
	{
		i = 0;
		while (i < len)
		{
			append[i] = s1[i];
			i++;
		}
		if (s1)
			free(s1);
		j = 0;
		while (j++ < n)
			append[i++] = *(s2++);
		if (append[i - 1] != '\0')
			append[i] = '\0';
	}
	return (append);
}

static size_t	ft_strlen(const char *s1)
{
	size_t	len;

	len = 0;
	while (s1 && *s1)
	{
		s1++;
		len++;
	}
	return (len);
}

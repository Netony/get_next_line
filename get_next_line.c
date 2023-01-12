/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:39:15 by dajeon            #+#    #+#             */
/*   Updated: 2023/01/12 15:41:42 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*append_n(char *s1, const char *s2, size_t s2_len);
static void		check_n_free(void *check);
static size_t	find_n(const void *m, int c, size_t n);
static size_t	len(const char *s1);

#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*stack;
	char		buf[BUFFER_SIZE];
	char		*temp;
	char		*ret;
	int			buf_size;
	size_t		ret_size;

	while (stack == NULL || !find_n(stack, '\n', len(stack)))
	{
		buf_size = read(fd, buf, BUFFER_SIZE);
		if (buf_size == -1)
		{
			check_n_free(stack);
			return (NULL);
		}
		stack = append_n(stack, buf, buf_size);
		if (buf_size == 0)
			break ;
	}
	if (!find_n(stack, '\n', len(stack)))
	{
		ret = append_n(NULL, stack, len(stack));
		temp = NULL;
	}
	else
	{
		ret_size = find_n(stack, '\n', len(stack));
		ret = append_n(NULL, stack, ret_size);
		temp = append_n(NULL, stack + ret_size, len(stack) - ret_size);
	}
	check_n_free(stack);
	stack = temp;
	return (ret);
}

static size_t	find_n(const void *m, int c, size_t n)
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

static char	*append_n(char *s1, const char *s2, size_t s2_len)
{
	size_t	s1_len;
	size_t	i;
	size_t	j;
	char	*append;

	s1_len = len(s1);
	if (s1_len + s2_len == 0)
		return (NULL);
	append = (char *)malloc(sizeof(char) * (1 + s1_len + s2_len));
	if (append)
	{
		i = 0;
		while (i < s1_len)
		{
			append[i] = s1[i];
			i++;
		}
		check_n_free(s1);
		j = 0;
		while (j < s2_len)
		{
			append[i + j] = s2[j];
			j++;
		}
		append[i + j] = '\0';
	}
	return (append);
}

static size_t	len(const char *s1)
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

static void	check_n_free(void *check)
{
	if (check == NULL)
		return ;
	else
	{
		free(check);
		check = NULL;
	}
}

	

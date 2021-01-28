/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apending <apending@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:43:07 by apending          #+#    #+#             */
/*   Updated: 2020/11/30 18:42:04 by apending         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_strichr(char *str, int sumb)
{
	int i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == (char)sumb)
			return (i);
	}
	return (-1);
}

char	*ft_strdup(const char *str)
{
	char	*res;
	char	*p;
	size_t	size;

	size = (size_t)ft_strlen((char*)str) + 1;
	if (!(res = malloc(size * sizeof(char))))
		return (0);
	p = res;
	while (*str)
	{
		*res = *str;
		str++;
		res++;
	}
	*res = 0;
	return (p);
}

void	*ft_memmove(void *dest, const void *source, size_t count)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = -1;
	p1 = (unsigned char *)dest;
	p2 = (unsigned char *)source;
	if (dest == source)
		return (dest);
	if (dest > source)
		while (count--)
			p1[count] = p2[count];
	else
		while (++i != count)
			p1[i] = p2[i];
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	size;
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	size = len1 + len2 + 1;
	if (!(res = malloc(size * sizeof(char))))
		return (0);
	if (s1)
		ft_memmove((void *)res, (const void *)s1, len1);
	ft_memmove((void *)(res + len1), (const void *)s2, len2);
	*(res + size - 1) = 0;
	if (s1)
		free(s1);
	return (res);
}

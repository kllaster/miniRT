#include "mini_rt.h"

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	if (!s)
		return ;
	i = -1;
	while (++i < n)
	{
		*((char *)s) = 0;
		++s;
	}
}

float	ft_fabs(float num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	i = 0;
	while ((str1[i] || str2[i]) && n > i)
	{
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		++i;
	}
	return (0);
}

int		ft_strequal_end(char *str, char *end)
{
	int i;
	int a;

	if (!str)
		return (0);
	a = ft_strlen(end);
	i = ft_strlen(str);
	while (i >= 0 && a >= 0 && str[i] == end[a])
	{
		--i;
		--a;
	}
	if (a == -1)
		return (1);
	return (0);
}

void	*ft_memcpy(void *dest, const void *source, size_t count)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	if (dest == source)
		return (dest);
	i = -1;
	p1 = (unsigned char *)dest;
	p2 = (unsigned char *)source;
	while (++i != count)
		p1[i] = p2[i];
	return (dest);
}

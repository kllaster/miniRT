/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apending <apending@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:14:57 by apending          #+#    #+#             */
/*   Updated: 2020/11/30 20:08:56 by apending         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_end_gnl(int error, char **line, char **line_buff)
{
	if (error == -1 || error == 0)
	{
		if (error == -1 && line)
		{
			if (*line)
				free(*line);
			*line = NULL;
		}
		if (line_buff && *line_buff)
			free(*line_buff);
		*line_buff = NULL;
		return (error);
	}
	return (error);
}

static char	*ft_get_gnl_line(char **line, char *line_buff)
{
	int		i;
	int		index;
	char	*new_buff;

	if (!line_buff)
	{
		*line = ft_strdup("");
		return (ft_strdup(""));
	}
	index = ft_strichr(line_buff, '\n');
	if (index == -1)
		index = ft_strlen(line_buff);
	if (!(*line = malloc((index + 1) * sizeof(char))))
		return (0);
	i = -1;
	while (++i < index)
		(*line)[i] = line_buff[i];
	(*line)[i] = 0;
	if (line_buff[i] && line_buff[i + 1])
		if (!(new_buff = ft_strdup(line_buff + i + 1)))
			return (0);
	if (!line_buff[i] || !line_buff[i + 1])
		new_buff = ft_strdup("");
	free(line_buff);
	return (new_buff);
}

int			get_next_line(int fd, char **line)
{
	static char	*line_buff;
	char		buff[BUFFER_SIZE + 1];
	int			res;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buff, 0) == -1)
		return (ft_end_gnl(-1, NULL, &line_buff));
	while (ft_strichr(line_buff, '\n') == -1)
	{
		if ((res = read(fd, buff, BUFFER_SIZE)) == -1)
			return (ft_end_gnl(-1, line, &line_buff));
		if (!res && (line_buff = ft_get_gnl_line(line, line_buff))
			&& !(line_buff[0]))
			return (ft_end_gnl(0, line, &line_buff));
		else if (!res && !line_buff)
			return (ft_end_gnl(-1, line, &line_buff));
		else if (!res && *line && !line_buff[0])
			return (1);
		buff[res] = '\0';
		if (!(line_buff = ft_strjoin(line_buff, buff)))
			return (ft_end_gnl(-1, line, &line_buff));
	}
	if (!(line_buff = ft_get_gnl_line(line, line_buff)))
		return (ft_end_gnl(-1, line, &line_buff));
	return (1);
}

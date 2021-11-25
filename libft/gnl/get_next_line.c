/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:12:51 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:19:44 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	ft_free(char **line, char **buf, char **stat_buf, int ret)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	if (buf && *buf)
	{
		free(*buf);
		*buf = NULL;
	}
	if (stat_buf && *stat_buf)
	{
		free(*stat_buf);
		*stat_buf = NULL;
	}
	return (ret);
}

static	int	ft_search(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static	char	*new_str(int l)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)malloc(sizeof(char) * l + 1);
	if (!res)
		return (NULL);
	while (i < l)
	{
		res[i] = 0;
		i++;
	}
	res[l] = '\0';
	return (res);
}

static	int	ft_reader(char **line, char *buf, char **stat_buf, int fd)
{
	int	flag;
	int	bites;

	flag = 1;
	while (flag)
	{
		bites = read(fd, buf, 1024);
		if (bites < 0 || *line == NULL)
			return (ft_free(line, &buf, stat_buf, -1));
		buf[bites] = '\0';
		if (ft_search(buf))
		{
			*stat_buf = transposition(buf, *stat_buf, line);
			if (*stat_buf == NULL)
				return (ft_free(line, &buf, stat_buf, -1));
			flag = 0;
		}
		else
			*line = ft_strjoin_gnl(*line, buf);
		if (!bites)
			return (ft_free(NULL, &buf, stat_buf, 0));
	}
	return (ft_free(NULL, &buf, NULL, 1));
}

int	get_next_line(int fd, char **line)
{
	char			*buf;
	static char		*stat_buf[1024];

	if (!line || fd < 0)
		return (-1);
	if (fd < 0 || fd > 1024)
		return (-1);
	buf = malloc(sizeof(char) * (1024 + 1));
	if (!buf)
		return (-1);
	if (stat_buf[fd])
	{
		if (ft_search(stat_buf[fd]))
		{
			*line = new_str(1);
			stat_buf[fd] = transposition(stat_buf[fd], stat_buf[fd], line);
			return (ft_free(NULL, &buf, NULL, 1));
		}
		*line = ft_strdup_gnl(stat_buf[fd], '\0');
		if (*line == NULL)
			return (ft_free(line, &buf, &stat_buf[fd], -1));
	}
	else
		*line = new_str(1);
	return (ft_free(NULL, NULL, NULL, ft_reader(line, buf, &stat_buf[fd], fd)));
}

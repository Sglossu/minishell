/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:12:49 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:12:50 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_gnl(const char *str, char c)
{
	char			*my_str;
	int				i;
	int				size;

	i = 0;
	size = ft_strlen_gnl(str);
	my_str = malloc(sizeof(char) * (size + 1));
	if (my_str == NULL)
		return (0);
	while (str[i] != c)
	{
		my_str[i] = str[i];
		i++;
	}
	my_str[i] = '\0';
	return (my_str);
}

char	*ft_strdup_next_gnl(const char *str)
{
	char			*my_str;
	int				i;
	int				size;
	int				k;

	i = 0;
	k = 0;
	size = ft_strlen_gnl(str);
	while (str[i] != '\n')
		i++;
	i++;
	my_str = malloc(sizeof(char) * (size + 1 - i));
	if (my_str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		my_str[k] = str[i];
		i++;
		k++;
	}
	my_str[k] = '\0';
	return (my_str);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	int		i;
	int		sum;
	char	*str;
	int		k;

	k = 0;
	i = 0;
	if ((char *)s1 == NULL || (char *)s2 == NULL)
		return (NULL);
	sum = ft_strlen_gnl((char *)s1) + ft_strlen_gnl((char *)s2);
	str = (char *)malloc(sizeof(char) * (sum + 1));
	if (str == NULL)
		return (NULL);
	while (sum && s1[i] != '\0' && sum--)
		str[i++] = s1[k++];
	k = 0;
	while (sum-- && s2[k] != '\0')
	{
		str[i++] = s2[k++];
	}
	str[i] = '\0';
	free(s1);
	s1 = NULL;
	return (str);
}

size_t	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}

char	*transposition(char *buf, char *static_buf, char **line)
{
	char	*static_buf_tmp;
	char	*buf_tmp;

	buf_tmp = ft_strdup_gnl(buf, '\n');
	static_buf_tmp = static_buf;
	static_buf = ft_strdup_next_gnl(buf);
	free(static_buf_tmp);
	*line = ft_strjoin_gnl(*line, buf_tmp);
	if (*line == NULL)
		return (NULL);
	free(buf_tmp);
	return (static_buf);
}

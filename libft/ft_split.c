/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:59:54 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:59:55 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_free(char **buf)
{
	int	i;

	i = 0;
	if (buf != NULL)
	{
		while (buf[i] != NULL)
			free(buf[i++]);
		free(buf);
	}
	return (NULL);
}

static	void	put_the_words(char **buf, char *str, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (str[k] != '\0')
	{
		j = 0;
		while (str[k] == c)
		{
			k++;
		}
		while (str[k] != c && str[k] != '\0')
		{
			buf[i][j] = str[k];
			j++;
			k++;
		}
		i++;
	}
}

static	char	**count_symbols(char **buf, char *str, char c)
{
	int	count_symbol;
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (str[j] != '\0')
	{
		count_symbol = 0;
		while (str[j] == c)
			j++;
		while (str[j] != c && str[j] != '\0')
		{
			j++;
			count_symbol++;
		}
		if (count_symbol != 0)
		{
			buf[i] = (char *)malloc(sizeof(char) * (count_symbol + 1));
			if (buf[i] == NULL)
				return (ft_free(buf));
			buf[i++][count_symbol] = '\0';
		}
	}
	return (buf);
}

static	int	all_split_string(char *str, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[j] != '\0')
	{
		if (str[j] == c)
		{
			if (str[j + 1] != c && str[j + 1] != '\0')
				i++;
		}
		j++;
	}
	if (str[0] != '\0' && str[0] != c)
		i++;
	return (i);
}

char	**ft_split(char *str, char c)
{
	int		i;
	char	**buf;
	int		j;
	int		count;

	if (str == NULL)
		return (NULL);
	count = 0;
	j = 0;
	i = all_split_string(str, c);
	buf = (char **)malloc(sizeof(char *) * (i + 1));
	if (buf == NULL)
		return (NULL);
	buf[i] = NULL;
	if (count_symbols(buf, str, c) == NULL)
		return (NULL);
	put_the_words(buf, str, c);
	return (buf);
}

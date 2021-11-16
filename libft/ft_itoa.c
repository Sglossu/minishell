/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:15:36 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:15:37 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_fulling(char *str, int n, int size)
{
	int	x;

	if (n == -2147483648)
	{
		n = -214748364;
		str[size - 1] = '8';
		size--;
	}
	x = 0;
	if (n < 0)
		n = -n;
	while (size != 0)
	{
		x = n % 10;
		str[size - 1] = x + '0';
		size--;
		n /= 10;
	}
	return (str);
}

static	int	ft_size(int n)
{
	int	size;

	if (n < 0)
		size = 2;
	else
		size = 1;
	while (n)
	{
		if ((n / 10) == 0)
			return (size);
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;

	size = ft_size(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	str = ft_fulling(str, n, size);
	if (n < 0)
		str[0] = '-';
	return (str);
}

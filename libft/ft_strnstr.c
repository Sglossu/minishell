/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:16:26 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:16:27 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	len2;

	if (ft_strlen((char *)str1) < ft_strlen((char *)str2))
		return (NULL);
	if (*str2 == '\0' && *str1 != '\0')
		return ((char *)str1);
	if (*str2 == '\0' && *str1 == '\0')
		return ((char *)str1);
	len2 = ft_strlen((char *)str2);
	while (*str1 != '\0' && len != 0)
	{
		if (*str1 == *str2 && len >= len2)
			if (ft_strncmp(str1, str2, len2) == 0)
				return ((char *)str1);
		str1++;
		len--;
	}
	return (NULL);
}

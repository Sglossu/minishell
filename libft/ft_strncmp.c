/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:16:28 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:16:29 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (((unsigned char)str1[i] != '\0' && (unsigned char)str2[i] != '\0') \
	&& i < n)
	{
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	if (((unsigned char)str1[i] != '\0' || (unsigned char)str2[i] != '\0') \
	&& i < n)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}

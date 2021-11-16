/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:16:35 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:16:36 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		sum;
	char	*str;
	int		k;

	k = 0;
	i = 0;
	if ((char *)s1 == NULL || (char *)s2 == NULL)
		return (NULL);
	sum = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * (sum + 1));
	if (str == NULL)
		return (NULL);
	while (sum && s1[i] != '\0')
	{
		str[i++] = s1[k++];
		sum--;
	}
	k = 0;
	while (sum-- && s2[k] != '\0')
	{
		str[i++] = s2[k++];
	}
	str[i] = '\0';
	return (str);
}

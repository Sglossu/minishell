/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:16:37 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:16:38 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char			*my_str;
	int				i;
	int				size;

	i = 0;
	size = ft_strlen(str);
	my_str = malloc(sizeof(char) * (size + 1));
	if (my_str == NULL)
		return (0);
	while (str[i])
	{
		my_str[i] = str[i];
		i++;
	}
	my_str[i] = '\0';
	return (my_str);
}

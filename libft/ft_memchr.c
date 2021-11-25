/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:15:31 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:15:32 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t count)
{
	unsigned char	*buf2;
	unsigned char	c2;

	buf2 = (unsigned char *)buf;
	c2 = (unsigned char)c;
	while (count)
	{
		if (*buf2 == c2)
			return (buf2);
		count--;
		buf2++;
	}
	return (NULL);
}

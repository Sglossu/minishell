/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:13:14 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:13:15 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t n)
{
	size_t			i;
	unsigned char	*m_dst;

	m_dst = dst;
	i = 0;
	while (i != n)
	{
		m_dst[i] = c;
		i++;
	}
	return (m_dst);
}

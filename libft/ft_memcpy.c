/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:15:26 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:15:27 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*m_dst;
	unsigned char	*m_src;
	size_t			i;

	m_dst = (unsigned char *)dst;
	m_src = (unsigned char *)src;
	i = 0;
	if (m_dst == NULL && m_src == NULL)
		return (NULL);
	while (i != n)
	{
		m_dst[i] = m_src[i];
		i++;
	}
	return (m_dst);
}

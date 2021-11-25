/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:15:24 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:15:25 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*m_dst;
	unsigned char	*m_src;
	size_t			i;

	m_dst = (unsigned char *)dst;
	m_src = (unsigned char *)src;
	i = 0;
	if (m_dst == NULL && m_src == NULL)
		return (0);
	if (m_dst < m_src)
	{
		while (len-- > 0)
		{
			m_dst[i] = m_src[i];
			i++;
		}
	}
	else
	{
		while (++i <= len)
			m_dst[len - i] = m_src[len - i];
	}
	return (m_dst);
}

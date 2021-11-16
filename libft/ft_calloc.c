/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:15:50 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:15:51 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	all_size;
	void	*buf;

	all_size = count * size;
	buf = malloc(all_size);
	if (!buf)
		return (NULL);
	ft_memset(buf, 0, all_size);
	return (buf);
}

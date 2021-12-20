/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:21:58 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 22:22:59 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, char *key)
{
	while (lst)
	{
		if (!ft_strncmp(lst->val, key, ft_strlen(key)) && \
		(ft_strlen(key) == ft_strlen(lst->val)
				|| lst->val[ft_strlen(key)] == '='))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

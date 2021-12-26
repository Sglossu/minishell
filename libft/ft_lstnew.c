/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:26:02 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/16 22:26:04 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *val)
{
	t_list	*new_elem;

	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	new_elem->val = val;
	new_elem->flag_delete = DELETE;
	new_elem->next = NULL;
	return (new_elem);
}

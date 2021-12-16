/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:56:38 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/14 18:17:10 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	compare(char *s1, char *s2)
{
	int	k;

	k = 0;
	while (s1[k] == s2[k] && s1[k] != '\0' && s2[k] != '\0')
		k++;
	return (s1[k] - s2[k]);
}

void	sort_params(int argc, char **argv)
{
	char	*str;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (i < argc)
	{
		j = i + 1;
		while (j < argc)
		{
			if (compare(argv[i], argv[j]) > 0)
			{
				str = argv[i];
				argv[i] = argv[j];
				argv[j] = str;
			}
			j++;
		}
		i++;
	}
}

char	**ft_sort_params(int argc, t_list *lst)
{
	char	**argv;

	argv = from_lst_to_buf(argc, lst, '\0');
	if (argv == NULL)
		return (NULL);
	sort_params(argc, argv);
	return (argv);
}

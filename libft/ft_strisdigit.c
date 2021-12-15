//
// Created by Shasta Glossu on 12/14/21.
//

#include "libft.h"

int	ft_strisdigit(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1); // есть буква
		i++;
	}
	return (0); // нет буков, тока циферы
}
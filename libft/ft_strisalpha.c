//
// Created by Shasta Glossu on 12/14/21.
//

#include "libft.h"

int	ft_strisalpha(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (1); // есть цифра
			i++;
	}
	return (0); // только буквы
}
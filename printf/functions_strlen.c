#include "ft_printf.h"

int	ft_strlen_p(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen_nb(unsigned long nb)
{
	unsigned int	count;

	count = 1;
	while ((nb / 10) != 0)
	{
		count += 1;
		nb /= 10;
	}
	return (count);
}

int	ft_strlen_inint(unsigned int nb)
{
	unsigned int	count;

	count = 1;
	while ((nb / 10) != 0)
	{
		count += 1;
		nb /= 10;
	}
	return (count);
}

int	ft_diglen16(unsigned int nb)
{
	unsigned int	count;

	count = 1;
	while ((nb / 16) != 0)
	{
		count += 1;
		nb /= 16;
	}
	return (count);
}

int	ft_diglenlong(unsigned long nb)
{
	unsigned int	count;

	count = 1;
	while ((nb / 16) != 0)
	{
		count += 1;
		nb /= 16;
	}
	return (count);
}

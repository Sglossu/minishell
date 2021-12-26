#include "../includes/minishell.h"

char	*change_shlvl(char *str_old)
{
	char	*str_new;
	int 	shlvl;
	char	*nb_str;

	shlvl = ft_atoi(str_old + 6);
	if (!ft_isdigit(str_old[6]) && str_old[6] != '-') // 1 - есть цифра
		str_new = ft_strdup("SHLVL=1");
	else if (shlvl == 0)
		str_new = ft_strdup("SHLVL=1");
	else if (shlvl < 0)
		str_new = ft_strdup("SHLVL=0");
	else if (shlvl >= 999)
		str_new = ft_strdup("SHLVL=");
	else
	{
		nb_str = ft_itoa(shlvl + 1);
		if (!nb_str)
			return (NULL);
		else
			str_new = ft_strjoin("SHLVL=", nb_str);
	}
	if (!str_new)
		return (NULL);
	return (str_new);
}
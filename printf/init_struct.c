#include "ft_printf.h"

t_struct	first_init_struct(t_struct ptf)
{
	ptf.flag = '1';
	ptf.width = 0;
	ptf.accuracy = -2;
	ptf.i = 0;
	ptf.count = 0;
	ptf.minus = 0;
	ptf.space = 0;
	ptf.temp = 0;
	ptf.temp_w = 0;
	return (ptf);
}

t_struct	second_init_struct(t_struct ptf)
{
	ptf.flag = '1';
	ptf.width = 0;
	ptf.accuracy = -2;
	ptf.minus = 0;
	ptf.space = 0;
	ptf.temp = 0;
	ptf.temp_w = 0;
	return (ptf);
}

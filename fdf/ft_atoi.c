#include "fdf.h"

int	ft_atoi(char *str)
{
	int		i;
	int		n;
	long	r;

	i = 0;
	n = 1;
	r = 0;
	while ((str[i] == ' ' || str[i] == '\f' || str[i] == '\n') || \
			(str[i] == '\r' || str[i] == '\t' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -n;
		i++;
	}	
	while (str[i] > 47 && str[i] < 58)
	{
		r = (str[i] - '0') + (r * 10);
		if ((r * n < -2147483648) || (r * n > 2147483647))
			return ((r * n < -2147483648) - 1);
		i++;
	}
	return (r * n);
}

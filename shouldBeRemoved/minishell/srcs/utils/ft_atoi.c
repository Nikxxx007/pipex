#include "utils.h"

static int	issign(char c)
{
	if (c == '-')
		return (-1);
	if (c == '+')
		return (1);
	return (0);
}

static int	too_long(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		out;
	int		sign;
	size_t	cur_len;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (issign(*str))
		sign = issign(*(str++));
	cur_len = 0;
	out = 0;
	while (ft_isdigit(*str))
	{
		out = out * 10 + (*(str++) - '0') * sign;
		cur_len++;
		if (cur_len == 20)
			return (too_long(sign));
	}
	return (out);
}

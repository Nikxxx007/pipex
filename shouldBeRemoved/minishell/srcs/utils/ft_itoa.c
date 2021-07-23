#include "utils.h"

static int	num_of_digits(int n)
{
	int		len;

	len = 0;
	while ((n / 10))
	{
		n /= 10;
		len++;
	}
	return (len + 1);
}

static void	get_sign(int n, int *sign)
{
	if (n < 0)
		*sign = 1;
	else
		*sign = 0;
}

char	*ft_itoa(int n)
{
	char	*out;
	int		sign;
	int		len;
	int		tmp;

	get_sign(n, &sign);
	len = num_of_digits(n);
	out = (char *)malloc(sizeof(char) * (len + sign + 1));
	if (!out)
		return (NULL);
	out[len + sign] = 0;
	if (sign)
		out[0] = '-';
	while (--len >= 0)
	{
		tmp = n % 10;
		if (tmp < 0)
			tmp *= -1;
		out[len + sign] = tmp + '0';
		n /= 10;
	}
	return (out);
}

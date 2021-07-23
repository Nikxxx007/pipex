#include "utils.h"

int	ft_islower(char c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_isupper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

int	ft_isalpha(char c)
{
	return (ft_isupper(c) || ft_islower(c));
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

#include <limits.h>

static int	check_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f')
}

static int	check_ll_overflow(long long res, int sign)
{
	if (sign == 1 && res > LLONG_MAX)
		return (0);
	else if (sign == -1 && -res < LLONG_MIN)
		return (0);
	else
		return (1);
}

long long	ft_atoll(const char *str)
{
	long long		res;
	int				sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (check_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if (!check_ll_overflow(res, sign))
			return (0);
	}
	return (res * sign);
}

static int	check_int_overflow(long res, int sign)
{
	if (sign == 1 && res > INT_MAX)
		return (0);
	else if (sign == -1 && -res < INT_MIN)
		return (0);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	long			res;
	long			sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (check_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if (!check_int_overflow(res, sign))
			return (0);
	}
	return ((int)(res * sign));
}

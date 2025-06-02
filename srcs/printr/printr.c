/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:08:41 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/15 17:01:20 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putchar(char c)
{
	write(2, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
		i++;
	write(2, str, i);
	return (i);
}

int	ft_putnbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		i = i + ft_putstr("-2147483648");
		return (i);
	}
	if (n < 0)
	{
		ft_putchar('-');
		i++;
		n = n * -1;
	}
	if (n >= 10)
	{
		i = i + ft_putnbr(n / 10);
		i = i + ft_putchar(n % 10 + '0');
	}
	else
		i = i + ft_putchar(n + '0');
	return (i);
}

int	ft_putunsigned(unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (ft_putchar('0'));
	if (n >= 10)
	{
		i = i + ft_putunsigned(n / 10);
		i = i + ft_putchar(n % 10 + '0');
	}
	else
		i = i + ft_putchar(n + '0');
	return (i);
}

int	printr(const char *str, ...)
{
	va_list	args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	if (!str || (str[0] == '%' && !str[1]))
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			j = j + ft_conversions(args, str[i]);
		}
		else
			j = j + ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (j);
}

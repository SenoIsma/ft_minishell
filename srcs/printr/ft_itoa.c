/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:43:41 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/07 09:51:40 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	ft_write(char *str, int n, int sign, int j)
{
	int	i;

	i = j - 1;
	if (sign == 1)
		str[0] = '-';
	while (n > 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	str[j] = '\0';
	write(2, str, j);
	return (j);
}

int	ft_itoa_printf(int n)
{
	int		j;
	char	*str;
	int		sign;

	j = 0;
	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"), 11);
	if (n == 0 || n == -0)
		return (ft_strdup("0"), 1);
	j = ft_count(n);
	if (n < 0)
	{
		n = n * -1;
		j = 1 + ft_count(n);
		sign = 1;
	}
	else
		j = ft_count(n);
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (-1);
	ft_write(str, n, sign, j);
	free(str);
	return (j);
}

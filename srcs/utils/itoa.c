/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:54:14 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/12 16:35:49 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	size;
	char	*dup;

	i = 0;
	size = ft_strlen(s);
	dup = malloc(sizeof(char) * size + 1);
	if (dup == NULL)
		return (NULL);
	while (i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

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

static char	*ft_write(char *str, int n, int sign, int j)
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
	return (str);
}

char	*ft_itoa(int n)
{
	int		j;
	char	*str;
	int		sign;

	j = 0;
	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0 || n == -0)
		return (ft_strdup("0"));
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
		return (NULL);
	ft_write(str, n, sign, j);
	return (str);
}

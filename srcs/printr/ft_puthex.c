/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:56:26 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/05/25 19:15:54 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_puthexmaj(unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n >= 16)
	{
		i = i + ft_puthexmaj(n / 16);
		if (n % 16 < 10)
			i = i + ft_putchar(n % 16 + '0');
		else
			i = i + ft_putchar(n % 16 + 55);
	}
	else
	{
		if (n % 16 < 10)
			i = i + ft_putchar(n % 16 + '0');
		else
			i = i + ft_putchar(n % 16 + 55);
	}
	return (i);
}

static int	ft_puthexmin(unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n >= 16)
	{
		i = i + ft_puthexmin(n / 16);
		if (n % 16 < 10)
			i = i + ft_putchar(n % 16 + '0');
		else
			i = i + ft_putchar(n % 16 + 87);
	}
	else
	{
		if (n % 16 < 10)
			i = i + ft_putchar(n % 16 + '0');
		else
			i = i + ft_putchar(n % 16 + 87);
	}
	return (i);
}

int	ft_puthex(unsigned int n, int maj)
{
	if (maj == 0)
		return (ft_puthexmin(n));
	else
		return (ft_puthexmaj(n));
}

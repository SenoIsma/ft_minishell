/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakerken <sakerken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:03:10 by sakerken          #+#    #+#             */
/*   Updated: 2024/11/21 00:50:18 by sakerken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_return(int flg, int fd)
{
	if (!flg)
		ft_putstr_fd("\n", fd);
	if (fd > 2)
		close(fd);
	return (0);
}

int	is_n_flag(const char *str)
{
	int	i;

	i = 1;
	if (str && str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	echo_print(t_token **args, int fd)
{
	t_token	*tmp;

	tmp = *args;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == STRING)
		{
			ft_putstr_fd(tmp->content, fd);
			if (tmp->next && tmp->next->type == STRING)
				ft_putstr_fd(" ", fd);
		}
		tmp = tmp->next;
	}
}

int	ft_echo(t_token **args)
{
	int		fd;
	int		fl_n;
	t_token	*tmp;

	fd = 1;
	fl_n = 0;
	fd = get_fd(args);
	tmp = (*args)->next;
	if (tmp->type == NOTHING)
		return (exit_return(0, fd));
	while (tmp && tmp->type == STRING && is_n_flag(tmp->content))
	{
		fl_n = 1;
		tmp = tmp->next;
	}
	echo_print(&tmp, fd);
	return (exit_return(fl_n, fd));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:57:49 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 19:57:00 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	simple_command(t_data *data)
{
	if (ft_init_fd(data->start) == FALSE)
		return (FALSE);
	which_exec(data);
	return (FALSE);
}

static int	pipes_first(t_data *data, int i)
{
	if (dup2(data->pipex.fds[i][1], STDOUT_FILENO) == -1)
		return (FALSE);
	close(data->pipex.fds[i][1]);
	if (ft_init_fd(data->start) == FALSE)
		return (FALSE);
	return (TRUE);
}

static int	pipes_middle(t_data *data, int i)
{
	if (dup2(data->pipex.fds[i - 1][0], STDIN_FILENO) == -1)
		return (FALSE);
	else
		close(data->pipex.fds[i - 1][0]);
	if (dup2(data->pipex.fds[i][1], STDOUT_FILENO) == -1)
		return (FALSE);
	else
		close(data->pipex.fds[i][1]);
	if (ft_init_fd(data->start) == FALSE)
		return (FALSE);
	return (TRUE);
}

static int	pipes_last(t_data *data, int i)
{
	if (dup2(data->pipex.fds[i - 1][0], STDIN_FILENO) == -1)
		return (FALSE);
	else
		close(data->pipex.fds[i - 1][0]);
	if (ft_init_fd(data->start) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	run_command_with_pipes(t_data *data, int i)
{
	if (data->pipex.nb_cmd < 2)
	{
		if (simple_command(data) == FALSE)
			return (FALSE);
	}
	if (i == 0)
	{
		if (pipes_first(data, i) == FALSE)
			return (FALSE);
	}
	else if (i < data->pipex.nb_cmd - 1)
	{
		if (pipes_middle(data, i) == FALSE)
			return (FALSE);
	}
	else
	{
		if (pipes_last(data, i) == FALSE)
			return (FALSE);
	}
	close_pipes(data->pipex.fds, data->pipex.nb_cmd);
	which_exec(data);
	return (FALSE);
}

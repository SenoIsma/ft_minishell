/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:58:31 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 17:59:10 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_forkouille(t_data *data, int i)
{
	data->pipex.pid[i] = fork();
	if (data->pipex.pid[i] == -1)
		return (perror("fork failed"), FALSE);
	if (i > 0)
	{
		while (data->start && data->start->type != PIPE
			&& data->start->type != NOTHING)
			data->start = data->start->next;
		if (data->start && data->start->type == PIPE && data->start->next)
			data->start = data->start->next;
	}
	if (data->pipex.pid[i] == 0)
	{
		set_child_signals();
		if (run_command_with_pipes(data, i) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int	ft_fork(t_data *data)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < data->pipex.nb_cmd)
	{
		if (ft_forkouille(data, i) == FALSE)
			return (FALSE);
		i++;
	}
	close_pipes(data->pipex.fds, data->pipex.nb_cmd);
	status = ft_wait(&data->pipex, data->pipex.nb_cmd);
	if (data->pipex.sigint == 1)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (data->pipex.sigquit == 1)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	data->status = status;
	return (TRUE);
}

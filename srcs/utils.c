/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:15:46 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 20:34:30 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	failed_pipes(int i, int **fds)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(fds[j]);
		free(fds);
		j++;
	}
}

int	**create_pipes(int cmd_count)
{
	int	**fds;
	int	i;

	i = 0;
	if (cmd_count < 2)
		return (NULL);
	fds = malloc(sizeof(int *) * (cmd_count - 1));
	if (!fds)
		return (NULL);
	while (i < cmd_count - 1)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (fds[i] == NULL || pipe(fds[i]) == -1)
			return (failed_pipes(i, fds), NULL);
		i++;
	}
	return (fds);
}

void	close_pipes(int **fds, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		free(fds[i]);
		i++;
	}
	free(fds);
}

int	ft_wait(t_pipex *pipex, int count_cmd)
{
	int	i;
	int	status;

	i = 0;
	while (i < count_cmd)
	{
		if (waitpid(pipex->pid[i], &status, 0) == -1)
			return (1);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
		if (status == 128 + SIGINT)
			pipex->sigint = 1;
		else if (status == 128 + SIGQUIT)
			pipex->sigquit = 1;
		++i;
	}
	return (status);
}

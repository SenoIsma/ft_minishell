/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:24:43 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 19:55:09 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_bis(t_token *cur, int *fd)
{
	if (cur->type == OUTFILE || cur->type == OUTFILE_D)
	{
		*fd = open_outfile(cur);
		if (*fd > 2)
		{
			dup2(*fd, STDOUT_FILENO);
			close(*fd);
		}
	}
	if (cur->type == INFILE)
	{
		*fd = open_infile(cur);
		if (*fd == 0)
			return (FALSE);
		if (*fd > 2)
		{
			dup2(*fd, STDIN_FILENO);
			close(*fd);
		}
	}
	return (TRUE);
}

int	ft_init_fd(t_token *cur)
{
	int	fd;

	fd = 0;
	while (cur && cur->type != PIPE)
	{
		if (init_bis(cur, &fd) == FALSE)
			return (FALSE);
		cur = cur->next;
	}
	return (TRUE);
}

int	open_outfile(t_token *tmp)
{
	int	fd;

	fd = 1;
	if (tmp->type == OUTFILE)
	{
		fd = open(tmp->next->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return ((perror("open"), FALSE));
	}
	if (tmp->type == OUTFILE_D)
	{
		fd = open(tmp->next->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return ((perror("open"), FALSE));
	}
	return (fd);
}

int	open_infile(t_token *tmp)
{
	int	fd;

	fd = open(tmp->next->content, O_RDONLY, 0644);
	if (fd == -1)
		return ((perror("open"), FALSE));
	if (ft_strncmp(tmp->next->content, "heredoc.tmp", 12) == 0)
		unlink("heredoc.tmp");
	return (fd);
}

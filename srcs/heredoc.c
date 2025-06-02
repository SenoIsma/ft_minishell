/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakerken <sakerken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:17:22 by kali              #+#    #+#             */
/*   Updated: 2024/11/21 19:12:13 by sakerken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_heredocs(t_token **args, int h)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *args;
	while (tmp && i <= h)
	{
		if (tmp->type == INFILE && ft_strncmp(tmp->next->content, "heredoc.tmp",
				12) == 0)
			tmp->type = HERE_DOC;
		tmp = tmp->next;
		i++;
	}
}

void	check_heredocs(t_token **args)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *args;
	while (tmp)
	{
		if (tmp->type == INFILE && ft_strncmp(tmp->next->content, "heredoc.tmp",
				12) == 0)
			i++;
		tmp = tmp->next;
	}
	if (i >= 2)
		rm_heredocs(args, i);
}

/*
	plus besoin de close chaque heredocs 
	j'essaie de les close et de garder le nom du fichier
	pour l'ouvrir dans l'exec
*/

int	print_in_file(int fd, char *lim)
{
	char	*str;

	while (1)
	{
		if (g_waiting == 3)
			return (close(fd), FALSE);
		str = readline("> ");
		if (g_waiting == 1)
			return (close(fd), free(str), FALSE);
		if (!str)
		{
			close(fd);
			printr("minishell: warning: here-document at line 1 ");
			printr("delimited by end-of-file (wanted `%s')\n", lim);
		}
		if (ft_strcmp(lim, str) == 0)
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
	}
	return (close(fd), TRUE);
}

int	ft_heredoc(t_token **args, char *lim, t_data *data)
{
	int		fd;
	t_token	*last;

	g_waiting = 2;
	fd = open("heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), FALSE);
	if (print_in_file(fd, lim) == FALSE)
		return (data->status = 130, FALSE);
	last = ft_tokenlast(*args);
	ft_free(last->content);
	last->content = ft_strdup("<");
	last->type = INFILE;
	ft_tokenadd(args, ft_tokennew(FICHIER, ft_strdup("heredoc.tmp"), TRUE));
	return (TRUE);
}

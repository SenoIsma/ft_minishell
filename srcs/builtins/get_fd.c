/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:37:35 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 19:02:21 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_outfile(t_token **args)
{
	t_token	*cur;
	int		nb;

	nb = 0;
	cur = *args;
	while (cur && cur->type != PIPE)
	{
		if ((cur->type == OUTFILE || cur->type == OUTFILE_D) && cur->next
			&& cur->next->type == FICHIER)
			nb++;
		cur = cur->next;
	}
	return (nb);
}

static int	get_fd_bis(t_token *cur, int i, int fd, int nb)
{
	while (cur && cur->type != PIPE)
	{
		if ((cur->type == OUTFILE || cur->type == OUTFILE_D) && cur->next
			&& cur->next->type == FICHIER)
		{
			if (i < nb - 1)
			{
				fd = open_outfile(cur);
				if (fd == -1)
					return (printr("Error : open fd (get_fd)\n"), -1);
				close(fd);
				i++;
			}
			else
				return (open_outfile(cur));
		}
		cur = cur->next;
	}
	return (1);
}

int	get_fd(t_token **args)
{
	t_token	*cur;
	int		nb;
	int		i;
	int		fd;

	fd = 0;
	i = 0;
	nb = nb_outfile(args);
	cur = *args;
	fd = get_fd_bis(cur, i, fd, nb);
	if (fd == -1)
		return (-1);
	return (fd);
}

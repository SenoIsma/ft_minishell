/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakerken <sakerken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:02:32 by kali              #+#    #+#             */
/*   Updated: 2024/11/21 19:14:42 by sakerken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_token *args, t_data *data)
{
	int		fd;
	t_env	*tmp;

	tmp = data->env;
	fd = get_fd(&args);
	if (fd == -1)
		return (2);
	if (args->next->type != NOTHING && args->next->type != PIPE
		&& args->next->type != INFILE && args->next->type != HERE_DOC
		&& args->next->type != OUTFILE && args->next->type != OUTFILE_D)
		return (printr("minishell: env: too many arguments\n"), 1);
	while (tmp)
	{
		ft_putstr_fd(tmp->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(tmp->value, fd);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
	}
	if (fd != 1)
		close(fd);
	return (0);
}

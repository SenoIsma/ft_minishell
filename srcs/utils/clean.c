/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakerken <sakerken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:34:36 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/19 23:18:46 by sakerken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char *content)
{
	free (content);
	content = NULL;
}

void	ft_clean(t_data *data)
{
	if (data->env)
		ft_free_lst(data->env);
	if (data->line)
		ft_free(data->line);
	if (data->token)
		ft_free_token(data->token);
	if (data->pipex.pid)
		free(data->pipex.pid);
	if (data->envp)
		ft_free_tab(data->envp);
	ft_bzero(&data->pipex, sizeof(t_pipex));
	rl_clear_history();
}

void	ft_clean_loop(t_data *data)
{
	free(data->line);
	if (data->token)
		ft_free_token(data->token);
	data->token = NULL;
	if (data->pipex.pid)
		free(data->pipex.pid);
	ft_bzero(&data->pipex, sizeof(t_pipex));
}

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		ft_free(tab[i]);
		i++;
	}
	free(tab);
}

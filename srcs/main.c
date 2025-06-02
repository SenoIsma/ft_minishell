/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:08:52 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 20:26:56 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_waiting = 0;

void	ft_verif(t_data *data)
{
	if (!data->line)
	{
		ft_clean(data);
		printf("exit\n");
		exit(0);
	}
	if (ft_strcmp(data->line, "") != 0)
		add_history(data->line);
}

int	minishell(t_data *data)
{
	if (ft_strcmp(data->line, "") != 0 && parsing(data->line, &data->token,
			data) == TRUE && ft_strcmp(data->token->content, "") != 0)
	{
		data->start = data->token;
		set_parent_exec_signals();
		check_heredocs(&data->token);
		data->pipex.nb_cmd = count_cmd(&data->token);
		if (data->pipex.nb_cmd == 1 && is_builtin(data->token))
			which_exec(data);
		else
		{
			data->pipex.pid = malloc(sizeof(pid_t) * data->pipex.nb_cmd);
			if (!data->pipex.pid)
				return (FALSE);
			data->pipex.fds = create_pipes(data->pipex.nb_cmd);
			if (ft_fork(data) == FALSE)
				return (FALSE);
		}
		get_args_or_cmd(data);
	}
	return (update_envp(data->env, data), TRUE);
}

int	run_minishell_loop(t_data *data)
{
	while (1)
	{
		ft_signal();
		g_waiting = 0;
		data->line = readline("minishell$ ");
		if (g_waiting == 1)
		{
			data->status = 130;
			continue ;
		}
		ft_verif(data);
		if (ft_syntax_analysis(data->line) == TRUE)
		{
			if (minishell(data) == FALSE)
				break ;
		}
		else
			data->status = 2;
		ft_clean_loop(data);
	}
	return (ft_clean(data), 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	if (argc != 1)
		return (printr("Error: too many arguments\n"), EXIT_FAILURE);
	split_env(&data.env, envp);
	run_minishell_loop(&data);
	return (1);
}

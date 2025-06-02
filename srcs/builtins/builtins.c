/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakerken <sakerken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:17:33 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/21 18:43:43 by sakerken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_last(t_env **env, char *last)
{
	t_env	*tmp;

	tmp = key_exist(env, "_");
	if (tmp != NULL)
	{
		ft_free(tmp->value);
		tmp->value = ft_strdup(last);
	}
	else
		ft_lstadd(env, ft_lstnew("_", ft_strdup(last)));
}

void	get_args_or_cmd(t_data *data)
{
	t_token	*cur;
	char	*cmd;
	char	*arg;

	cmd = NULL;
	arg = NULL;
	cur = data->start;
	if (!cur)
		return ;
	while (cur->type != NOTHING)
	{
		if (cur->type == PIPE)
			return ;
		if (cur->type == CMD)
			cmd = cur->content;
		if (cur->type == STRING)
			arg = cur->content;
		cur = cur->next;
	}
	if (cmd && !arg)
		update_last(&data->env, cmd);
	else if (cmd && arg)
		update_last(&data->env, arg);
	else
		update_last(&data->env, "");
}

void	which_exec(t_data *data)
{
	if (data->start->type == NOTHING)
	{
		printf("\n");
		return ;
	}
	if (is_builtin(data->start))
		exec_builtins(data);
	else
		ft_exec(data);
	return ;
}

void	exec_builtins(t_data *data)
{
	if (ft_strcmp(data->start->content, "exit") == 0)
		data->status = ft_exit(data, &data->start);
	else if (ft_strcmp(data->start->content, "echo") == 0)
		data->status = ft_echo(&data->start);
	else if (ft_strcmp(data->start->content, "cd") == 0)
		data->status = ft_cd(&data->start, &data->env);
	else if (ft_strcmp(data->start->content, "pwd") == 0)
		data->status = ft_pwd(data);
	else if (ft_strcmp(data->start->content, "env") == 0)
		data->status = ft_env(data->start, data);
	else if (ft_strcmp(data->start->content, "export") == 0)
		data->status = ft_export(&data->start, data->env, data);
	else if (ft_strcmp(data->start->content, "unset") == 0)
		data->status = ft_unset(&data->start, data->env, data);
	update_envp(data->env, data);
}

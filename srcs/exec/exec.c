/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:36:53 by sakerken          #+#    #+#             */
/*   Updated: 2024/11/22 19:04:11 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_lvl(t_env *env, t_data *data)
{
	t_env	*tmp;
	int		lvl;

	lvl = 1;
	tmp = NULL;
	tmp = key_exist(&env, "SHLVL");
	if (tmp != NULL)
	{
		lvl = ft_atoi(tmp->value);
		ft_free(tmp->value);
		tmp->value = ft_itoa(lvl + 1);
	}
	else
		ft_lstadd(&env, ft_lstnew("SHLVL", ft_itoa(lvl + 1)));
	update_envp(env, data);
}

void	exit_exec(char **path, int ret, char **cmd, t_data *data)
{
	char	*str;

	ft_free_tab(path);
	if (ret < 0)
	{
		str = ft_returnline(cmd[0]);
		if (!str)
			return (ft_free_tab(cmd), ft_clean(data));
		ft_free_tab(cmd);
		ft_clean(data);
		if (ret == -127 || ret == -1)
		{
			printr("minishell : %s : command not found\n", str);
			free(str);
			exit(127);
		}
		else if (ret == -126)
		{
			printr("minishell : %s : Permission denied\n", str);
			free(str);
			exit(126);
		}
	}
	ft_free_tab(cmd);
}

char	*get_cmd_path(char *path, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	tmp = ft_strjoin("/", cmd);
	if (tmp == NULL)
		return (NULL);
	cmd_path = ft_strjoin(path, tmp);
	if (cmd_path == NULL)
		return (NULL);
	free(tmp);
	return (cmd_path);
}

int	ft_exec_ret(char *cmd_path, char **cmd, t_data *data)
{
	int	ret;

	ret = 0;
	if (access(cmd_path, F_OK) == -1)
		return (-127);
	if (access(cmd_path, X_OK) == -1)
		return (-126);
	if (ft_strcmp("./minishell", cmd_path) == 0 || ft_strcmp("minishell",
			cmd_path) == 0)
		add_lvl(data->env, data);
	update_envp(data->env, data);
	ret = execve(cmd_path, cmd, data->envp);
	return (ret);
}

void	ft_exec(t_data *data)
{
	char	**path;
	char	**cmd;
	char	*cmd_path;
	int		exec_ret;
	int		i;

	exec_ret = -1;
	i = 0;
	go_to_cmd(data);
	cmd = join_cmd(&data->start);
	if (!cmd)
		return ;
	path = ft_split(get_path(data->env), ':');
	if (!path)
		return ;
	while (path && path[++i])
	{
		cmd_path = get_cmd_path(path[i], cmd[0]);
		if (!cmd_path)
			return ;
		exec_ret = ft_exec_ret(cmd_path, cmd, data);
		free(cmd_path);
	}
	exec_ret = ft_exec_ret(cmd[0], cmd, data);
	exit_exec(path, exec_ret, cmd, data);
}

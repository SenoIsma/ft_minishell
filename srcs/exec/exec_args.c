/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:22:15 by kali              #+#    #+#             */
/*   Updated: 2024/11/22 20:36:05 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_size(t_token *cur)
{
	int	i;

	i = 0;
	while (cur && cur->type != PIPE \
	&& (cur->type == CMD || cur->type == STRING))
	{
		cur = cur->next;
		i++;
	}
	return (i);
}

void	go_to_cmd(t_data *data)
{
	t_token	*cur;

	cur = data->start;
	while (cur->type != NOTHING)
	{
		if (cur->type == CMD)
		{
			data->start = cur;
			break ;
		}
		cur = cur->next;
	}
	if (data->start->type != CMD)
	{
		ft_clean(data);
		exit(0);
	}
}

char	**join_cmd(t_token **args)
{
	t_token	*cur;
	char	**cmd;
	int		i;
	int		y;

	cur = *args;
	y = 0;
	i = cmd_size(cur);
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	cur = *args;
	while (y < i)
	{
		if (cur->type != NOTHING)
			cmd[y] = ft_strdup(cur->content);
		else
			cmd[y] = NULL;
		y++;
		cur = cur->next;
	}
	cmd[y] = NULL;
	return (cmd);
}

char	*get_path(t_env *env)
{
	t_env	*path_env;

	path_env = env;
	while (path_env)
	{
		if (ft_strcmp(path_env->key, "PATH") == 0)
			return (path_env->value);
		path_env = path_env->next;
	}
	return (".");
}

char	*ft_returnline(char *s)
{
	int		i;
	char	*cmd;

	cmd = NULL;
	i = ft_strlenln(s);
	cmd = malloc(sizeof(char) * (i + 1));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, i + 1);
	ft_strln(cmd, s);
	return (cmd);
}

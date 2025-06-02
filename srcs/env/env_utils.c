/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:33:44 by sakerken          #+#    #+#             */
/*   Updated: 2024/11/19 19:08:09 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_env(t_env **lst)
{
	ft_lstadd(lst, ft_lstnew(ft_strdup("PWD"), get_pwd()));
	ft_lstadd(lst, ft_lstnew(ft_strdup("SHLVL"), ft_strdup("1")));
	ft_lstadd(lst, ft_lstnew(ft_strdup("_"), ft_strdup("./minishell")));
	return ;
}

void	split_env(t_env **lst, char **envp)
{
	int		i;
	int		y;
	char	*key;
	char	*value;

	if (!envp || !*envp)
		return (create_env(lst));
	i = 0;
	while (envp[i])
	{
		y = 0;
		while (envp[i][y] != '=')
			y++;
		key = ft_substr(envp[i], 0, y);
		value = ft_substr(envp[i], y + 1, ft_strlen(envp[i]));
		ft_lstadd(lst, ft_lstnew(key, value));
		i++;
	}
}

t_env	*key_exist(t_env **env, char *key)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

static void	envp_bis(t_env *env, t_data *data, char **new_envp)
{
	t_env	*tmp;
	int		i;
	char	*tmp_key;

	tmp_key = NULL;
	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp_key = ft_strjoin(tmp->key, "=");
		new_envp[i] = ft_strjoin(tmp_key, tmp->value);
		ft_free(tmp_key);
		i++;
		tmp = tmp->next;
	}
	new_envp[i] = NULL;
	ft_free_tab(data->envp);
	data->envp = new_envp;
}

void	update_envp(t_env *env, t_data *data)
{
	t_env	*tmp;
	char	**new_envp;
	int		size;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	new_envp = (char **)malloc((size + 1) * sizeof(char *));
	if (!new_envp)
		return ;
	envp_bis(env, data, new_envp);
}

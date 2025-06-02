/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:01:55 by kali              #+#    #+#             */
/*   Updated: 2024/11/22 18:39:40 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env, int fd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd(tmp->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(tmp->value, fd);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
	}
	close(fd);
}

void	add_value(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = key_exist(&env, key);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
	}
	else
	{
		if (value)
			ft_lstadd(&env, ft_lstnew(ft_strdup(key), ft_strdup(value)));
		else
			ft_lstadd(&env, ft_lstnew(ft_strdup(key), NULL));
	}
	ft_free(key);
	ft_free(value);
}

int	process_export(t_token **args, t_env *env)
{
	t_token	*tmp;
	char	*key;
	char	*value;

	tmp = (*args)->next;
	while (tmp->type == STRING)
	{
		key = NULL;
		value = NULL;
		get_key_value(tmp, &key, &value);
		if (check_key(key))
		{
			printr("minishell : export : %s : not a valid identifier\n", key);
			return (ft_free(key), ft_free(value), 1);
		}
		if (key)
			add_value(env, key, value);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(t_token **args, t_env *env, t_data *data)
{
	int	fd;

	fd = get_fd(&data->start);
	if (fd == -1)
		return (2);
	if ((*args)->next->type != STRING)
	{
		print_env(env, fd);
		if (fd != 1)
			close(fd);
		return (0);
	}
	if (fd != 1)
		close(fd);
	return (process_export(args, env));
}

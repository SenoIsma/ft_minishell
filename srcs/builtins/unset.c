/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakerken <sakerken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:01:01 by kali              #+#    #+#             */
/*   Updated: 2024/11/21 17:09:56 by sakerken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_env_node(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = key_exist(env, key);
	if (!tmp)
		return ;
	if (tmp == *env)
	{
		*env = tmp->next;
		if (*env)
			(*env)->prev = NULL;
	}
	else
	{
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

int	ft_unset(t_token **args, t_env *env, t_data *data)
{
	t_token	*current;
	int		fd;

	fd = get_fd(&data->start);
	if (fd == -1)
		return (2);
	if (fd != 1)
		close(fd);
	current = *args;
	current = current->next;
	while (current && current->type == STRING)
	{
		rm_env_node(&env, current->content);
		current = current->next;
	}
	return (0);
}

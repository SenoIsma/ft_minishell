/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:39:28 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 18:41:22 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_key_value(t_token *args, char **key, char **value)
{
	int	i;

	i = 0;
	if (ft_strchr(args->content, '=') == NULL)
	{
		*key = ft_strdup(args->content);
		*value = NULL;
		return ;
	}
	while (args->content[i] && args->content[i] != '=')
		i++;
	if (i == 0)
		*key = ft_strdup("=");
	else
		*key = ft_substr(args->content, 0, i);
	*value = ft_substr(args->content, i + 1, ft_strlen(args->content) - i - 1);
}

int	check_key(char *arg)
{
	int	i;

	i = 0;
	if ((arg[0] >= '0' && arg[0] <= '9') || arg[0] == '-')
		return (1);
	while (arg[i])
	{
		if (!((arg[i] >= '0' && arg[i] <= '9') \
		|| (arg[i] >= 'a' && arg[i] <= 'z') \
		|| (arg[i] >= 'A' && arg[i] <= 'Z') \
		|| arg[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

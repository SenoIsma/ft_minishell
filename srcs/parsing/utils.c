/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:43:41 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 18:34:08 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*choose_key(char *line, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	if (ft_strcmp(line, "") == 0)
		return ("$");
	while (tmp)
	{
		if (ft_strcmp(tmp->key, line) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

int	ft_checkalnum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || \
	(c >= 'a' && c <= 'z') || (c == '_'))
		return (1);
	return (0);
}

char	*get_key(char *line, t_data *data)
{
	int		i;
	int		j;
	char	*ret;
	char	*var;

	i = 1;
	j = i;
	ret = NULL;
	var = NULL;
	if (ft_strncmp(line, "$?", 2) == 0)
		return (ft_itoa(data->status));
	while (line[i] && !is_token(line[i]) && !is_whitespace(line[i]) \
	&& ft_checkalnum(line[i]))
		i++;
	var = ft_substr(line, j, i - j);
	ret = ft_strdup(choose_key(var, data));
	ft_free(var);
	return (ret);
}

int	show_last_type(t_token **args)
{
	t_token	*tmp;
	int		type;

	type = -1;
	if (!args)
		return (-1);
	tmp = *args;
	while (tmp)
	{
		type = tmp->type;
		tmp = tmp->next;
	}
	return (type);
}

int	choose_type(t_token **args)
{
	int	last_type;

	last_type = show_last_type(args);
	if (last_type == -1)
		return (CMD);
	else if (last_type == INFILE || last_type == OUTFILE \
	|| last_type == OUTFILE_D)
		return (FICHIER);
	else if (last_type == PIPE || last_type == FICHIER)
		return (CMD);
	else if (last_type == HERE_DOC)
		return (LIM);
	else
		return (STRING);
}

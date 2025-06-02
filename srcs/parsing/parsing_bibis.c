/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bibis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:35:58 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 18:33:12 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_variable(char *line, int *i, t_data *data)
{
	char	*var;
	int		j;

	j = *i;
	if (ft_strncmp(&line[j], "$?", 2) == 0)
	{
		var = get_key(&line[j], data);
		*i += 2;
	}
	else
	{
		var = get_key(&line[j], data);
		j++;
		while (!is_token(line[j]) && !is_whitespace(line[j]) \
		&& ft_checkalnum(line[j]))
			j++;
		*i = j;
	}
	return (var);
}

static char	*extract_text(char *line, int *i)
{
	int		start;
	char	*text;

	start = *i;
	while (line[*i] != '$' && line[*i] != '"')
		(*i)++;
	text = ft_substr(line, start, *i - start);
	return (text);
}

char	*ft_double_quote(char *line, t_data *data)
{
	int		i;
	char	*ret;
	char	*tmp;
	char	*segment;

	i = 0;
	ret = NULL;
	while (line[i] != '"')
	{
		if (line[i] == '$')
			segment = process_variable(line, &i, data);
		else
			segment = extract_text(line, &i);
		tmp = ret;
		ret = ft_strjoin(ret, segment);
		ft_free(tmp);
		ft_free(segment);
	}
	return (ret);
}

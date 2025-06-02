/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:49:32 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 19:11:31 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_simple(char *line, t_token **args, int *i)
{
	int		j;
	int		type;
	char	*content;

	content = NULL;
	type = choose_type(args);
	j = 0;
	if (line[*i] != '\0' && line[*i] == '\'')
	{
		(*i)++;
		j = (*i);
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		content = ft_substr(line, j, (*i) - j);
		(*i)++;
		if (ft_strcmp(content, "") == 0 || !content)
			type = NOTHING;
		if (is_whitespace(line[*i]))
			ft_tokenadd(args, ft_tokennew(type, content, TRUE));
		else
			ft_tokenadd(args, ft_tokennew(type, content, FALSE));
	}
	return (TRUE);
}

int	parsing_double(char *line, int *i, t_data *data)
{
	int		type;
	char	*content;

	content = NULL;
	type = choose_type(&data->token);
	if (line[*i] == '"')
	{
		(*i)++;
		content = ft_double_quote(&line[*i], data);
		while (line[*i] != '"')
			(*i)++;
		(*i)++;
		if (ft_strcmp(content, "") == 0 || !content)
			type = NOTHING;
		if (is_whitespace(line[*i]))
			ft_tokenadd(&data->token, ft_tokennew(type, content, TRUE));
		else
			ft_tokenadd(&data->token, ft_tokennew(type, content, FALSE));
	}
	return (TRUE);
}

void	ft_free_onetoken(t_token *freeable)
{
	free(freeable->content);
	freeable->content = NULL;
	freeable->next = NULL;
	freeable->space = 0;
	freeable->type = 0;
	free(freeable);
}

int	parsing(char *line, t_token **args, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] && is_whitespace(line[i]) && !is_token(line[i]))
			i++;
		if (parsing_simple(line, args, &i) == FALSE)
			return (FALSE);
		if (parsing_double(line, &i, data) == FALSE)
			return (FALSE);
		if (parsing_redir(line, args, &i) == FALSE)
			return (FALSE);
		if (parsing_pipe(line, &i, data) == FALSE)
			return (FALSE);
		if (parsing_dollar(line, &i, data) == FALSE)
			return (FALSE);
		if (parsing_other(line, args, &i, data) == FALSE)
			return (FALSE);
	}
	ft_verif_token(args);
	ft_tokenadd(args, ft_tokennew(NOTHING, NULL, FALSE));
	return (TRUE);
}

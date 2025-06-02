/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:49:32 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 18:31:32 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_redir_bis(char *line, t_token **args, int *i)
{
	int	j;

	j = (*i);
	while (line[*i] && line[*i] == '<')
		(*i)++;
	if ((*i) - j == 2)
	{
		ft_tokenadd(args, ft_tokennew(HERE_DOC, \
		ft_substr(line, j, (*i) - j), TRUE));
	}
	else
		ft_tokenadd(args, ft_tokennew(INFILE, \
		ft_substr(line, j, (*i) - j), TRUE));
	return (TRUE);
}

int	parsing_redir(char *line, t_token **args, int *i)
{
	int	j;

	j = 0;
	if (line[*i] != '\0' && line [*i] == '>')
	{
		j = (*i);
		while (line[*i] && line[*i] == '>')
			(*i)++;
		if ((*i) - j == 2)
		{
			ft_tokenadd(args, ft_tokennew(OUTFILE_D, \
			ft_substr(line, j, (*i) - j), TRUE));
		}
		else
		{
			ft_tokenadd(args, ft_tokennew(OUTFILE, \
			ft_substr(line, j, (*i) - j), TRUE));
		}
	}
	else if (line[*i] != '\0' && line [*i] == '<')
	{
		if (parsing_redir_bis(line, args, i) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int	parsing_pipe(char *line, int *i, t_data *data)
{
	if (line [*i] == '|')
	{
		ft_tokenadd(&data->token, ft_tokennew(PIPE, ft_strdup("|"), TRUE));
		(*i)++;
	}
	return (TRUE);
}

int	parsing_dollar(char *line, int *i, t_data *data)
{
	char	*content;

	content = NULL;
	if (line[*i] == '$')
	{
		content = get_key(&line[*i], data);
		if (ft_strncmp(&line[*i], "$?", 2) == 0)
			(*i) = (*i) + 2;
		else
		{
			(*i)++;
			while (line[*i] && !is_whitespace(line[*i]) && !is_token(line[*i]) \
			&& ft_checkalnum(line[*i]))
				(*i)++;
		}
		if (is_whitespace(line[*i]))
			ft_tokenadd(&data->token, ft_tokennew(choose_type(&data->token), \
			content, TRUE));
		else
			ft_tokenadd(&data->token, ft_tokennew(choose_type(&data->token), \
			content, FALSE));
	}
	return (TRUE);
}

int	parsing_other(char *line, t_token **args, int *i, t_data *data)
{
	int		j;
	char	*content;
	int		space;

	j = 0;
	space = FALSE;
	if (line[*i] && !is_whitespace(line[*i]))
	{
		j = (*i);
		while (line[*i] && !is_whitespace(line[*i]) && !is_token(line[*i]))
			(*i)++;
		if (is_whitespace(line[*i]))
			space = TRUE;
		content = ft_substr(line, j, (*i) - j);
		if (choose_type(args) == LIM)
		{
			if (ft_heredoc(args, content, data) == FALSE)
				return (ft_free(content), unlink("heredoc.tmp"), FALSE);
			ft_free(content);
		}
		else
			ft_tokenadd(args, ft_tokennew(choose_type(args), \
			content, space));
	}
	return (TRUE);
}

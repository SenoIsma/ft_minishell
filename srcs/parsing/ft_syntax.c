/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:44:19 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/19 18:44:35 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_syntax_quote(char *line, int *i)
{
	if (line[*i] == '"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
		if (line[*i] == '\0')
			return (printr("syntax error, quote not close\n"), FALSE);
		(*i)++;
	}
	else if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (line[*i] == '\0')
			return (printr("syntax error, quote not close\n"), FALSE);
		(*i)++;
	}
	return (TRUE);
}

static int	ft_syntax_redir(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		(*i) += 2;
		while (line[*i] && is_whitespace(line[*i]))
			(*i)++;
		if (line[*i] == '\0' || line[*i] == '>')
		{
			printr("minishell: syntax error near unexpected token `%c'\n"\
			, line[*i]);
			return (FALSE);
		}
	}
	else if (line[*i] == '>' && line[*i + 1] != '>')
	{
		(*i)++;
		while (line[*i] && is_whitespace(line[*i]))
			(*i)++;
		if (line[*i] == '\0' || line[*i] == '>')
		{
			printr("minishell: syntax error near unexpected token `%c'\n"\
			, line[*i]);
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	ft_syntax_redir_bis(char *line, int *i)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		(*i) += 2;
		while (line[*i] && is_whitespace(line[*i]))
			(*i)++;
		if (line[*i] == '\0' || line[*i] == '<')
		{
			printr("minishell: syntax error near unexpected token `%c'\n"\
			, line[*i]);
			return (FALSE);
		}
	}
	else if (line[*i] == '<' && line[*i + 1] != '<')
	{
		(*i)++;
		while (line[*i] && is_whitespace(line[*i]))
			(*i)++;
		if (line[*i] == '\0' || line[*i] == '<')
		{
			printr("minishell: syntax error near unexpected token `%c'\n"\
			, line[*i]);
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	ft_syntax_pipe(char *line, int *i)
{
	if (line[*i] == '|' && (*i) != 0)
	{
		(*i)++;
		if (line[*i] == '|')
		{
			printr("minishell: syntax error near unexpected token `%c'\n"\
			, line[*i]);
			return (FALSE);
		}
		while (line[*i] && is_whitespace(line[*i]))
			(*i)++;
		if (line[*i] == '\0' || line[*i] == '|')
		{
			printr("minishell: syntax error: unexpected end of file\n");
			return (FALSE);
		}
	}
	else if (line[*i] == '|' && (*i) == 0)
	{
		printr("minishell: syntax error near unexpected token `|'\n");
		return (FALSE);
	}
	return (TRUE);
}

int	ft_syntax_analysis(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (FALSE);
	if (ft_strcmp(line, "!") == 0 || ft_strcmp(line, ":") == 0)
		return (FALSE);
	while (line[i])
	{
		while (line[i] && (is_whitespace(line[i]) || !is_stoken(line[i])))
			i++;
		if (ft_syntax_quote(line, &i) == FALSE)
			return (FALSE);
		if (ft_syntax_redir(line, &i) == FALSE)
			return (FALSE);
		if (ft_syntax_redir_bis(line, &i) == FALSE)
			return (FALSE);
		if (ft_syntax_pipe(line, &i) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

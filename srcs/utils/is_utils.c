/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:36:55 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/17 14:52:05 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
	c == '\v' || c == '\f' || c == '\r');
}

int	is_token(char c)
{
	return (c == '"' || c == '\'' || c == '|' || \
	c == '>' || c == '<' || c == '$');
}

int	is_stoken(char c)
{
	return (c == '"' || c == '\'' || c == '|' || \
	c == '>' || c == '<');
}

int	is_builtin(t_token *args)
{
	if (args->type == NOTHING)
		return (FALSE);
	else if (ft_strcmp(args->content, "exit") == 0)
		return (TRUE);
	else if (ft_strcmp(args->content, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(args->content, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(args->content, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(args->content, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(args->content, "export") == 0)
		return (TRUE);
	else if (ft_strcmp(args->content, "unset") == 0)
		return (TRUE);
	else
		return (FALSE);
}

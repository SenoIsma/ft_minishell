/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:17:04 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 19:27:19 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_verif_void(t_token **args)
{
	t_token	*tmp;

	tmp = *args;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, "") == 0)
			tmp->space = FALSE;
		tmp = tmp->next;
	}
}

static int	ft_verif_syntax(t_token **args)
{
	t_token	*tmp;

	tmp = *args;
	while (tmp && tmp->next)
	{
		if (tmp->type == OUTFILE || tmp->type == OUTFILE_D
			|| tmp->type == INFILE || tmp->type == HERE_DOC)
		{
			if (tmp->next->type == OUTFILE || tmp->next->type == OUTFILE_D
				|| tmp->next->type == INFILE || tmp->next->type == HERE_DOC
				|| tmp->next->type == PIPE)
			{
				printr("minishell: syntax error near unexpected token %s'\n",
					tmp->next->content);
				return (FALSE);
			}
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

static void	ft_strjoin_parsing(t_token *tmp, t_token *tmpp, char *freeable)
{
	while (tmp)
	{
		if (tmp->space == FALSE && tmp->next)
		{
			if (tmp->next->type == OUTFILE || tmp->next->type == OUTFILE_D
				|| tmp->next->type == INFILE || tmp->next->type == HERE_DOC
				|| tmp->next->type == PIPE)
			{
				tmp = tmp->next;
				continue ;
			}
			freeable = tmp->content;
			tmp->content = ft_strjoin(tmp->content, tmp->next->content);
			ft_free(freeable);
			tmpp = tmp->next;
			tmp->space = tmpp->space;
			tmp->next = tmp->next->next;
			ft_free_onetoken(tmpp);
		}
		else
			tmp = tmp->next;
	}
}

int	ft_verif_token(t_token **args)
{
	t_token	*tmp;
	t_token	*tmpp;
	char	*freeable;

	tmpp = NULL;
	freeable = NULL;
	ft_verif_void(args);
	tmp = *args;
	ft_strjoin_parsing(tmp, tmpp, freeable);
	if (ft_verif_syntax(args) == FALSE)
		return (FALSE);
	return (TRUE);
}

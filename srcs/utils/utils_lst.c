/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:33:31 by sakerken          #+#    #+#             */
/*   Updated: 2024/11/22 19:27:41 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tokennew(int type, char *content, int space)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		exit(1);
	new_node->type = type;
	new_node->content = content;
	new_node->space = space;
	new_node->next = NULL;
	return (new_node);
}

void	ft_tokenadd(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = ft_tokenlast(*lst);
	last->next = new;
}

t_token	*ft_tokenlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// void	ft_printtoken(t_token *lst)
// {
// 	t_token	*tmp;

// 	tmp = lst;
// 	while (tmp)
// 	{
// 		printf("type: %d, content: %s\n", tmp->type, tmp->content);
// 		tmp = tmp->next;
// 	}
// }

void	ft_free_token(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		tmp->content = NULL;
		tmp->type = 0;
		free(tmp);
	}
}

int	ft_tokensize(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

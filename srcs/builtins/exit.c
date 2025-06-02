/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:53:22 by sakerken          #+#    #+#             */
/*   Updated: 2024/11/22 18:07:25 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokensize_without_redir(t_token **args)
{
	t_token	*cur;
	int		count;

	cur = *args;
	count = 0;
	while (cur && cur->type != PIPE)
	{
		if (cur->type != OUTFILE && cur->type != OUTFILE_D
			&& cur->type != INFILE && cur->type != HERE_DOC
			&& cur->type != FICHIER)
			count++;
		cur = cur->next;
	}
	return (count);
}

long long	ft_atol_exit(const char *str, int *flg)
{
	long		i;
	long		sign;
	long long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -sign;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] > '7' && number >= 922337203685477580)
			*flg = 1;
		number = number * 10 + (str[i++] - '0');
	}
	return (number * sign);
}

int	is_piped(t_token **args)
{
	t_token	*cur;

	cur = *args;
	while (cur)
	{
		if (cur->type == PIPE)
			return (TRUE);
		cur = cur->next;
	}
	return (FALSE);
}

int	is_num(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (FALSE);
		if (n > 18)
			return (FALSE);
		i++;
		n++;
	}
	return (TRUE);
}

int	ft_exit(t_data *data, t_token **args)
{
	long long	num;
	int			flg;
	int			fd;

	num = 0;
	flg = 0;
	fd = get_fd(args);
	if (fd != 1)
		close(fd);
	if (is_piped(&data->token) == FALSE)
		printf("exit\n");
	if ((*args)->next->content && !is_num((*args)->next->content))
		return (printr("bash : exit : numeric argument required\n"),
			ft_clean(data), exit(2), 2);
	if (ft_tokensize_without_redir(args) >= 4)
		return (printr("minishell: exit: too many arguments\n"), 1);
	rl_clear_history();
	if ((*args)->next && (*args)->next->type != NOTHING)
	{
		num = ft_atol_exit((*args)->next->content, &flg);
		if (is_num((*args)->next->content) && !flg)
			return (ft_clean(data), exit(num), 0);
	}
	return (ft_clean(data), exit(0), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakerken <sakerken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:59:32 by kali              #+#    #+#             */
/*   Updated: 2024/11/21 17:59:26 by sakerken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	buff[1024];
	int		fd;

	fd = get_fd(&data->start);
	if (fd == -1)
		return (printr("minishell: Error : failed open fd\n"), 2);
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		ft_putstr_fd(buff, fd);
		ft_putstr_fd("\n", fd);
		if (fd != 1)
			close(fd);
		return (0);
	}
	else
		return (perror("getcwd error"), 1);
}

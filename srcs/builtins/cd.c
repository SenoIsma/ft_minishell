/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:32:50 by sakerken          #+#    #+#             */
/*   Updated: 2024/11/22 18:00:12 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char	buff[1024];
	char	*pwd;

	pwd = getcwd(buff, sizeof(buff));
	if (!pwd)
		return (NULL);
	return (ft_strdup(pwd));
}

void	update_pwd(t_env **env, char *pwd)
{
	t_env	*tmp;
	char	*cur_path;

	cur_path = get_pwd();
	if (cur_path == NULL)
		return ;
	tmp = key_exist(env, pwd);
	if (tmp != NULL)
	{
		ft_free(tmp->value);
		tmp->value = ft_strdup(cur_path);
	}
	else
		ft_lstadd(env, ft_lstnew(pwd, ft_strdup(cur_path)));
	free(cur_path);
}

int	ft_cd(t_token **args, t_env **env)
{
	const char	*home_dir;
	int			fd;

	fd = get_fd(args);
	if (fd == -1)
		return (2);
	if (fd != 1)
		close(fd);
	home_dir = NULL;
	if (ft_tokensize_without_redir(args) >= 4)
		return (printr("minishell: cd: too many arguments\n"), 1);
	update_pwd(env, "OLDPWD");
	if (((*args)->next == NULL || ft_strcmp((*args)->next->content, "")) == 0
		&& (*args)->next->type != PIPE)
	{
		home_dir = getenv("HOME");
		if (!home_dir || chdir(home_dir) != 0)
			return (printr("minishell: cd: HOME not set\n"), 1);
	}
	else if (chdir((*args)->next->content) != 0 && (*args)->next->type != PIPE)
		return (printr("minishell : cd  %s: No such file or directory\n",
				(*args)->next->content), 1);
	return (update_pwd(env, "PWD"), 0);
}

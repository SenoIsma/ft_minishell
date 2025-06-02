/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhlel <ibouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:40:22 by ibouhlel          #+#    #+#             */
/*   Updated: 2024/11/22 20:26:13 by ibouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

int	ft_strlenln(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			i++;
		else
			i++;
	}
	return (i);
}

void	ft_strln(char *cmd, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			i++;
			cmd[j] = '\\';
			j++;
			cmd[j] = 'n';
			j++;
		}
		else
		{
			cmd[j] = s[i];
			i++;
			j++;
		}
	}
}

void	malloc_envp(char **env, t_data *data)
{
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (env[size])
		size++;
	data->envp = (char **)malloc((size + 1) * sizeof(char *));
	if (data->envp == NULL)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		data->envp[i] = ft_strdup(env[i]);
		i++;
	}
	data->envp[i] = NULL;
}

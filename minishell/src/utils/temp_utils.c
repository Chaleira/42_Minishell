/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:32:54 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/17 20:08:03 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

char	**env_var(char *var, char **env)
{
	int		i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlenchr(env[i], '=')))
			return (&(env[i]));
		i++;
	}
	return (NULL);
}

void	change_env_variable(char *variable, char *value)
{
	char	**tmp;
	char	*join;

	tmp = env_var(variable, (*control())->envp);
	join = ft_strjoin(variable, "=");
	if (tmp)
	{
		free(*tmp);
		*tmp = ft_strjoin(join, value);
	}
	else
		(*control())->envp = env_copy((*control())->envp,
				ft_stradd(&join, value));
	free(join);
}

int	check_alpha(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_strrevcmp(char *s1, char *s2)
{
	int	i;
	int	s1_len;
	int	s2_len;

	if (!s1 || !s2)
		return (-1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	while (s1_len >= 0 || s2_len >= 0)
	{
		if (s1[s1_len] > s2[s2_len])
			return (1);
		if (s1[s1_len] < s2[s2_len])
			return (-1);
		s1_len++;
		s2_len++;
	}
	return (0);
}

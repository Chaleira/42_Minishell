/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:32:54 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/09 03:29:55 by plopes-c         ###   ########.fr       */
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

int	change_env_variable(char **env, char *variable, char *value)
{
	if (value)
		variable = ft_strjoin(variable, "=");
	env = env_copy(env, ft_strjoin(variable, value));
	return (0);
}

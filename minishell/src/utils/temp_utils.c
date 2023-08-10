/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:32:54 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/08 17:30:17 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_env_variable(char ***env, char *variable, char *value)
{
	int		i;
	int 	var_len;

	if (!env)
		return (0);
	var_len = ft_strlen(variable);
	i = 0;
	while (*env[i])
	{
		if (!ft_strncmp(*env[i], variable, var_len))
		{
			free(*env[i]);
			*env[i] = ft_strjoin(variable, value);
			return (1);
		}
		i++;
	}
	return (0);
}

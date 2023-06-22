/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:56:31 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/22 22:33:22 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_execute_no_input(char *print, char **flags, char **env);
// static void	export_execute_with_input(char *str);

void	export_prepare(t_command *command, int index)
{
	(void)index;
	if (!command->terminal[1])
		command->execute = export_execute_no_input;
	else if (!command->terminal[2])
	{
		if (!ft_isdigit(command->terminal[1][0]))
			ft_printf("success\n");
		command->execute = export_execute_no_input;
	}
	ft_printf("add: %s\n", command->terminal[1]);
}

static void	export_execute_no_input(char *print, char **flags, char **env)
{
	int i;
	(void)flags;
	if (print)
	{
		ft_printf();
	}
	else
	{
		i = 0;
		while (env[i])
		{
			ft_printf("declare -x %s\n", env[i]);
			i++;
		}
	}
}

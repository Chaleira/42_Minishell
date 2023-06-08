/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:31:03 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/08 18:46:50 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_execute(char *str)
{
	if (!str)
		return ;
	if (chdir(str))
		ft_printf("minishell: cd: %s: Not a directory\n", str);
}

void	cd_prepare(t_command *command, int index)
{
	int	args;

	args = 0;
	while (command->terminal[args])
		args++;
	if (args > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		command->valid = 0;
		return ;
	}
	command->exec_path = ft_strdup(command->terminal[index + 1]);
	if (command->main->pipes)
		command->execute = (void *)cd_execute;
	else
		cd_execute(command->exec_path);
	command->valid = 0;
}

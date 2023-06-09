/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:31:03 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/09 17:48:02 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_execute(char *str)
{
	if (!str)
		return ;
	if (chdir(str))
		ft_printf("minishell: cd: %s: Not a directory\n", str);
	(*control())->pwd = getcwd(NULL, 0);
}

void	cd_prepare(t_command *command, int index)
{
	int	args;

	command->parse = 0;
	args = 0;
	while (command->terminal[args] && !split_case(command->terminal[args]))
		args++;
	if (args > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		command->valid = 0;
		return ;
	}
	command->exec_path = ft_strdup(command->terminal[index + 1]);
	while (command->terminal[args])
	{
		(solve(command->terminal[args]))(command, args);
		args++;
	}
	if (command->main->pipes)
		command->execute = (void *)cd_execute;
	else if (command->valid)
	{
		cd_execute(command->exec_path);
		command->valid = 0;
	}
}

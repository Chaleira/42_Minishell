/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:31:03 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/14 19:00:38 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_execute(char *str)
{
	if (!str)
		return ;
	if (chdir(str))
	{
		ft_printf("minishell: cd: %s: Not a directory\n", str);
		return ;
	}
	free((*control())->prompt);
	(*control())->prompt = get_prompt();
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
		command->status = 1;
		return ;
	}
	command->exec_path = ft_strdup(command->terminal[index + 1]);
	if (command->terminal[args])
		(solve(command->terminal[args]))(command, args);
	if (command->main->pipes)
		command->execute = (void *)cd_execute;
	else if (command->valid)
	{
		cd_execute(command->exec_path);
		command->valid = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:19 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/07 14:50:07 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_prepare(t_command *command, int index)
{
	int	flag;

	flag = 0;
	if (!(command->terminal[index + 1]))
	{
		command->exec_path = ft_calloc(sizeof(char), 2);
		command->exec_path[0] = '\n';
	}
	else
	{
		flag = !(ft_strncmp(command->terminal[index + 1], "-n", 2));
		index += flag;
		if (flag && !(command->terminal[index + 1]))
			command->exec_path = ft_calloc(sizeof(char), 1);
		else if (command->terminal[index + 1])
		{
			command->exec_path = ft_unsplit(&command->terminal[index + 1], 0);
			if (flag)
				command->exec_path[ft_strlen(command->exec_path) - 1] = 0;
		}
		while (command->terminal[index])
			*command->terminal[index++] = 0;
	}
	command->execute = builtin_exec;
}

void	echo_exe(t_command *get)
{
	ft_printf("%s", get->aux);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:19 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/07 10:42:09 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_prepare(t_command *command, int index)
{	
	int	flag;

	if (!(command->terminal[index + 1]))
	{
		command->aux = ft_calloc(sizeof(char), 2);
		command->aux[0] = '\n';
		flag = 0;
	}
	if (command->terminal[index + 1])
	{
		flag = !(ft_strncmp(command->terminal[index + 1], "-n", 2));
		index += flag;
		command->aux = ft_unsplit(&command->terminal[index + 1], 0);
		while (command->terminal[index])
			*command->terminal[index++] = 0;
	}
	else
	{
		command->aux = ft_calloc(sizeof(char), 2);
		command->aux[0] = '\n';
	}
	if (flag)
		command->aux[ft_strlen(command->aux) - 1] = 0;
	command->execute = echo_exe;
}

void	echo_exe(t_command *get)
{
	ft_printf("%s", get->aux);
}

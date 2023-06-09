/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:54:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/09 16:59:49 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_prepare(t_command *command, int index)
{
	index = 0;
	while (command->main->envp[index])
	{
		if (!ft_strncmp("PWD=", command->main->envp[index], 4))
		{
			command->exec_path = ft_strdup(&command->main->envp[index][4]);
			ft_stradd(&command->exec_path, "\n");
		}
		index++;
	}
	command->parse = 0;
	command->execute = builtin_execute;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:54:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/01 11:06:33 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd_prepare(t_command *command, int index)
{
	(void)index;
	command->exec_path = ft_calloc(sizeof(char), PATH_MAX);
	command->exec_path = getcwd(command->exec_path, PATH_MAX);
	ft_stradd(&command->exec_path, "\n");
	if (!command->status)
		command->execute = builtin_execute;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:54:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/07/28 11:33:01 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd_prepare(t_command *command, int index)
{
	(void)index;
	command->exec_path = ft_strdup(
			&(*get_envaddress(command->main->envp, "PWD"))[4]);
	ft_stradd(&command->exec_path, "\n");
	command->parse = 0;
	if (!command->status)
		command->execute = builtin_execute;
}

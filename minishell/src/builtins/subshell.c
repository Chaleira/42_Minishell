/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:19:15 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/26 16:02:05 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	start_subshell(t_command *command, int index)
{
	command->id = fork();
	if (command->id)
	{
		index = 0;
		while (command->main->tokens[index] != command->terminal)
			index++;
		while (command->main->tokens[index]
			&& ft_strncmp(command->main->tokens[index][0], ")", 5))
			stop_command(command->main->tokens[index++]);
		command->main->tokens[index][0][0] = 0;
		waitpid(command->id, &command->main->status, 0);
	}
}

void	end_subshell(t_command *command)
{
	run_input(command->main);
	end_shell(command->main);
}

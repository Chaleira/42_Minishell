/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:25:26 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/15 14:02:57 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_condition_execute(t_command *command, int index)
{
	(void)index;
	run_input(command->main);
	ft_lstclear(&command->main->commands, delete_command);
	if (command->terminal[index][0] == '|' && command->main->status == 0)
		command->main->tokens = free_triple_pointer(command->main->tokens);
	else if (command->terminal[index][0] == '&' && command->main->status != 0)
		command->main->tokens = free_triple_pointer(command->main->tokens);
}

void	status_execute(char *print)
{
	ft_printf("%s\n", print);
	(*control())->status = 0;
}

void	status_prepare(t_command *command, int index)
{
	(void)index;
	command->exec_path = ft_itoa(command->main->status);
	command->execute = (void *)status_execute;
}
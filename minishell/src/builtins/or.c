/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:23:12 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/12 18:20:29 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_or_execute(t_command *command, int index)
{
	(void)index;
	command->parse = 0;
	if (valid_sequence(command->main->commands))
	{
		command->parse = 0;
		command->valid = 0;
		return ;
	}
	ft_lstadd_back(&command->main->commands, ft_lstnew((void *)command));
	run_input(command->main);
	ft_lstclear(&command->main->commands, delete_command);
	if (command->main->status < 0)
	{
		command->parse = 0;
		command->valid = 0;
	}
}

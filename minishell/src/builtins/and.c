/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:26:15 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/12 18:20:04 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	valid_sequence(t_list *node)
{
	while (node)
	{
		if (!((t_command *)node->content)->valid)
			return (0);
		node = node->next;
	}
	return (1);
}

void	check_and_execute(t_command *command, int index)
{
	(void)index;
	if (!valid_sequence(command->main->commands))
	{
		command->parse = 0;
		command->valid = 0;
		return ;
	}
	run_input(command->main);
	if (command->main->status < 0)
	{
		command->parse = 0;
		command->valid = 0;
	}
}
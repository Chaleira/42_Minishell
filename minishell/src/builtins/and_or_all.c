/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:25:26 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/12 18:20:52 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_condition_execute(t_command *command, int index)
{
	(void)index;
	run_input(command->main);
	ft_lstclear(&command->main->commands, delete_command);
	if (*command->terminal[index] == '|' && command->main->status == 0)
		free_triple_pointer(command->main->pieces);
	else if (*command->terminal[index] == '&' && command->main->status != 0)
		free_triple_pointer(command->main->pieces);
}

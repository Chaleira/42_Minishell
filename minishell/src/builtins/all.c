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

void	execute_list(t_command *command, int index)
{
	(void)index;
	ft_lstadd_back(&command->main->commands, ft_lstnew((void *)command));
	run_input(command->main);
	ft_lstclear(&command->main->commands, delete_command);
}
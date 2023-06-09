/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_direct copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:14:52 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/09 18:16:02 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	output_direct(t_command *command, int index)
{
	if (command->terminal[index + 2])
	{
		command->valid = 0;
		return ;
	}
	command->out_pipe[1] = open(command->terminal[index + 1], O_CREAT | O_WRONLY);
	*command->terminal[index + 1] = 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_direct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:14:52 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/09 18:30:39 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	append_direct(t_command *command, int index)
{
	if (command->terminal[index + 2])
	{
		command->valid = 0;
		return ;
	}
	command->out_pipe[1] = open(command->terminal[index + 1], O_APPEND | O_CREAT | O_WRONLY);
	if (command->out_pipe[1] < 0)
	{
		ft_printf("permission denied: %s\n", command->terminal[index + 1]);
		command->valid = 0;
		command->parse = 0;
		return ;
	}
	*command->terminal[index + 1] = 0;
}
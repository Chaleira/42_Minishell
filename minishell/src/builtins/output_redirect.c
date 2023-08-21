/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:29:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/08/07 19:35:24 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	output_redirect(t_command *command, int index)
{
	if (!isatty(command->out_pipe[1]) && command->out_pipe[1] > 0)
		close(command->out_pipe[1]);
	if (*(short *)command->terminal[index] == *(short *)">>")
		command->out_pipe[1] = open(command->terminal[index + 1],
				O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		command->out_pipe[1] = open(command->terminal[index + 1],
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (command->out_pipe[1] < 0)
	{
		command->status = 1;
		command->parse = 0;
		ft_printf("Error opening file: %s\n", command->terminal[index + 1]);
		return ;
	}
	command->out_pipe[0] = open("/dev/null", O_RDONLY);
	command->terminal[index + 1][0] = 0;
}

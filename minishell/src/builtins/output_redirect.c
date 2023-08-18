/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:29:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/08/17 20:13:22 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	output_redirect(t_command *command, int index)
{
	if (command->terminal[index + 1])
	{
		command->terminal[index + 1] = \
			input_expand(command->terminal[index + 1], command->main->envp, 1);
		remove_pair(command->terminal[index + 1], "\'\"");
	}
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
		command->exec_path = \
			ft_strjoin("Error opening file: ", command->terminal[index + 1]);
		ft_stradd(&command->exec_path, "\n");
		command->execute = builtin_execute;
		return ;
	}
	command->out_pipe[0] = open("/dev/null", O_RDONLY);
	command->terminal[index + 1][0] = 0;
}

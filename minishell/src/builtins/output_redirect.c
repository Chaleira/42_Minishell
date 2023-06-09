/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirectct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:14:52 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/09 18:28:40 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	output_redirect(t_command *command, int index)
{
	if (!ft_strncmp(command->terminal[index], ">>", 2))
		command->in_pipe[0] = open(command->terminal[index + 1], O_CREAT | O_RDWR);
	else
		command->in_pipe[0] = open(command->terminal[index + 1], O_CREAT | O_APPEND | O_RDWR);
	if (command->in_pipe[0] < 0)
	{
		command->valid = 0;
		command->parse = 0;
		ft_printf("Error opening file: %s\n", command->terminal[index + 1]);
		return ;
	}
	command->terminal[index + 1][0] = 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:48:50 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/12 18:17:53 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(t_command *command, int input);
void	loop_exit(t_command *command, int index, int input);

void	exit_execute(t_command *command, int index)
{
	int	input;

	input = 0;
	command->parse = 0;
	if (command->main->pipes)
		return ;
	ft_printf("exit\n");
	if (command->terminal[index + 1])
	{
		input = ft_atoi(command->terminal[index + 1]);
		loop_exit(command, index, input);
		if (command->terminal[index + 2])
		{
			ft_printf("minishell: exit: too many arguments\n");
			input = 1;
			do_exit(command, input);
		}
	}
	do_exit(command, input);
}

void	do_exit(t_command *command, int input)
{
	input_reset(command->main);
	free_split(command->main->paths);
	delete_command(command);
	exit(input);
}

void	loop_exit(t_command *command, int index, int input)
{
	int	i;

	i = 0;
	while (command->terminal[index + 1][i])
	{
		if (!ft_isdigit(command->terminal[index + 1][i]))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
				command->terminal[index + 1]);
			input = 1;
			do_exit(command, input);
		}
		i++;
	}
}

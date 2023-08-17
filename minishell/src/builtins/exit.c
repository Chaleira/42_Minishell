/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:48:50 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/17 14:27:10 by plopes-c         ###   ########.fr       */
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
	if (execute_now(command))
	{
		ft_printf("exit\n");
		do_exit(command, input);
	}
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
		if (!ft_isdigit(command->terminal[index + 1][i])
			&& (command->terminal[index + 1][0] != '-'
				&& command->terminal[index + 1][0] != '+'))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
				command->terminal[index + 1]);
			input = 2;
			do_exit(command, input);
		}
		i++;
	}
}

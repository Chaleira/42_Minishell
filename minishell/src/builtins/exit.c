/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:48:50 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/18 17:33:54 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(t_command *command, int input);
void	loop_exit(t_command *command, int index, int input);

void	exit_execute(t_command *command, int index)
{
	long long	input;

	input = 0;
	command->parse = 0;
	if (command->terminal[index + 1])
	{
		ft_printf("exit\n");
		if (command->terminal[index + 2])
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			command->status = 1;
			return ;
		}
		remove_pair(command->terminal[index + 1], "\'\"");
		input = ft_atoi(command->terminal[index + 1]);
		loop_exit(command, index, input);
	}
	if (execute_now(command))
		do_exit(command, input);
}

void	do_exit(t_command *command, int input)
{
	t_control	*get;

	get = command->main;
	get->status = input;
	delete_command(command);
	end_shell(get);
}

void	loop_exit(t_command *command, int index, int input)
{
	int	i;

	i = 0;
	while (command->terminal[index + 1][i])
	{
		if ((!ft_isdigit(command->terminal[index + 1][i])
			&& (command->terminal[index + 1][0] != '-'
				&& command->terminal[index + 1][0] != '+'))
					|| (!ft_strcmp(command->terminal[index + 1], "9223372036854775808")
						|| !ft_strcmp(command->terminal[index + 1], "-9223372036854775809")))
		{
			write(2, "minishell: exit: ", 17);
			write(2, command->terminal[index + 1],
				ft_strlen(command->terminal[index + 1]));
			write(2, ": numeric argument required\n", 29);
			input = 2;
			do_exit(command, input);
		}
		i++;
	}
}

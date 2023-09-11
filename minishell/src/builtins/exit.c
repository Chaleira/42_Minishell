/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:48:50 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/11 13:01:51 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(char *str, char **flag, char **env, t_command *command);
void	loop_exit(t_command *command, int index);

void	exit_execute(t_command *command, int index)
{
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
		command->exec_path = ft_strdup(command->terminal[index + 1]);
		loop_exit(command, index);
	}
	if (!command->status)
		command->execute = (void *)do_exit;
	if (execute_now(command))
		command->status = PARENT;
}

void	do_exit(char *str, char **flag, char **env, t_command *command)
{
	t_control	*get;

	(void)str;
	(void)flag;
	(void)env;
	get = command->main;
	if (command->exec_path)
	{
		get->status = ft_atoi(command->exec_path);
		command->status = get->status;
	}
	else
		get->status = 0;
	if (command->status == PARENT)
	{
		delete_command(command);
		end_shell(get);
	}
}

void	loop_exit(t_command *command, int index)
{
	int	i;

	i = 0;
	while (command->terminal[index + 1][i])
	{
		if ((!ft_isdigit(command->terminal[index + 1][i])
			&& (command->terminal[index + 1][0] != '-'
			&& command->terminal[index + 1][0] != '+'))
					|| (!ft_strcmp(command->terminal[index + 1]
						, "9223372036854775808")
						|| !ft_strcmp(command->terminal[index + 1]
							, "-9223372036854775809")))
		{
			write(2, "minishell: exit: ", 17);
			write(2, command->terminal[index + 1],
				ft_strlen(command->terminal[index + 1]));
			write(2, ": numeric argument required\n", 29);
			command->status = 2;
		}
		i++;
	}
}

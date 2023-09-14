/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:48:50 by plopes-c          #+#    #+#             */
/*   Updated: 2023/09/14 21:35:24 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(char *str, char **flag, char **env, t_command *command);
int		check_exit(t_command *command, char *str);
void	exit_help(t_command *command, int status);

void	exit_execute(t_command *command, int index)
{
	command->parse = 0;
	if (execute_now(command))
		ft_printf("exit\n");
	if (command->terminal[index + 1]
		&& !split_case(command->terminal[index + 1]))
	{
		if (check_exit(command, command->terminal[index + 1]))
			exit_help(command, 2);
		if (command->terminal[index + 2] && (!command->status)
			&& !split_case(command->terminal[index + 2]))
		{
			write(2, "minishell: exit: too many arguments\n", 37);
			command->status = 1;
			return ;
		}
		remove_pair(command->terminal[index + 1], "\'\"");
		command->exec_path = ft_strdup(command->terminal[index + 1]);
	}
	if (!command->status)
		command->execute = (void *)do_exit;
	if (execute_now(command))
		command->is_parent = PARENT;
}

void	do_exit(char *str, char **flag, char **env, t_command *command)
{
	(void)str;
	(void)flag;
	(void)env;
	if (command->status != 1 && command->status != 2)
		if (command->exec_path)
			command->status = ft_atoi(command->exec_path);
	exit_help(command, 0);
}

int	check_exit(t_command *command, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((!ft_isdigit(str[i])
				&& (str[0] != '-' && str[0] != '+'))
			|| (!ft_strcmp(str, "9223372036854775808")
				|| !ft_strcmp(str, "-9223372036854775809")))
		{
			write(2, "minishell: exit: ", 17);
			write(2, str,
				ft_strlen(str));
			write(2, ": numeric argument required\n", 29);
			command->status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

void	exit_help(t_command *command, int status)
{
	t_control	*get;

	if (status)
		command->status = status;
	get = command->main;
	if (command->status)
		get->status = command->status;
	if (execute_now(command))
	{
		delete_command(command);
		end_shell(get);
	}
}

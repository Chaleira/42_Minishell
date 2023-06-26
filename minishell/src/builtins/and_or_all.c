/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:25:26 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/26 12:12:01 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	stop_command(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		*(split[i]) = 0;
		i++;
	}
}

int	stop_next_command(char ***tokens, char **split)
{
	int	index;

	if (!tokens || !*tokens)
		return (0);
	index = 0;
	while (tokens[index] != split)
		index++;
	stop_command(split);
	while (tokens[index])
	{
		if (!ft_strncmp((tokens[index][0]), "||", 10) || **(tokens[index]) == ';'
			|| **(tokens[index]) == '&')
			return (1);
		else
			stop_command(tokens[index]);
		index++;
	}
	return (0);
}

void	bonus_execute(t_command *command, int index)
{
	(void)index;
	command->terminal[index][0] = 0;
	run_input(command->main);
	ft_lstclear(&command->main->commands, delete_command);
	if (command->main->status == 0 && command->terminal[index][0] == '|')
		stop_next_command(command->main->tokens, command->terminal);
	else if (command->main->status != 0 && command->terminal[index][0] == '&')
		stop_next_command(command->main->tokens, command->terminal);
}

// void	bonus_execute(t_command *command, int index)
// {
// 	(void)index;
// 	run_input(command->main);
// 	ft_lstclear(&command->main->commands, delete_command);
// 	if (command->main->status == 0 && command->terminal[index][0] == '|')
// 		command->main->tokens = free_triple_pointer(command->main->tokens);
// 	else if (command->main->status != 0 && command->terminal[index][0] == '&')
// 		command->main->tokens = free_triple_pointer(command->main->tokens);
// }

void	status_execute(char *print)
{
	ft_printf("%s\n", print);
	(*control())->status = 0;
}

void	status_prepare(t_command *command, int index)
{
	(void)index;
	command->exec_path = ft_itoa(command->main->status);
	command->execute = (void *)status_execute;
}
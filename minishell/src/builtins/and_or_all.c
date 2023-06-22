/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:25:26 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/22 19:39:16 by rteles-f         ###   ########.fr       */
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

int	next_command(char ***tokens, int index)
{
	if (!tokens || !*tokens)
		return (0);
	stop_command(tokens[index]);
	ft_printf("%s\n", tokens[index][0]);
	while (tokens[index])
	{
		if (!ft_strncmp(*(tokens[index]), "||", 2) || **(tokens[index]) == ';'
			|| **(tokens[index]) == '&')
		{
			HERE;
			return (1);
		}
		else
			stop_command(tokens[index]);
		index++;
	}
	return (0);
}

void	bonus_execute(t_command *command, int index)
{
	(void)index;
	run_input(command->main);
	ft_lstclear(&command->main->commands, delete_command);
	if (command->main->status == 0 && command->terminal[index][0] == '|')
		next_command(command->main->tokens, index);
	else if (command->main->status != 0 && command->terminal[index][0] == '&')
		next_command(command->main->tokens, index);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:25:26 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/27 14:45:49 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	find_parenthesis(char **split)
{
	int	i;

	if (!split || !*split)
		return (0);
	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i++], ')'))
			return (1);
	}
	return (0);
}

static int	stop_next_command(char ***tokens, char **split)
{
	int	index;

	if (!tokens || !*tokens)
		return (0);
	index = 0;
	while (tokens[index] != split)
		index++;
	while (tokens[index] && *(tokens[index]) && **(tokens[index]))
	{
		if ((**(tokens[index]) == '(' || (tokens[index][0][1]) == '('))
		{
			while (tokens[index] && !find_parenthesis(tokens[index]))
				stop_command(tokens[index++]);
			stop_command(tokens[index]);
			return (1);
		}
		else if ((!ft_strncmp(tokens[index][0], "||", 10))
			|| **(tokens[index]) == ';' || **(tokens[index]) == '&')
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
	run_input(command->main);
	ft_lstclear(&command->main->commands, delete_command);
	if ((command->main->status == 0 && command->terminal[index][0] == '|')
		|| (command->main->status != 0 && command->terminal[index][0] == '&'))
	{
		// THERE;
		jump_command(command, 0);
		stop_next_command(command->main->tokens, command->terminal);
	}
}

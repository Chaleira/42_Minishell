/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5reset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:34:23 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/15 15:30:34 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	end_shell(t_control *get)
{
	input_reset(get);
	free_split(get->paths);
	safe_free_null(&get->prompt);
	rl_clear_history();
	exit(get->status);
}

void	delete_command(void *command)
{
	t_command	*get;

	get = (t_command *)command;
	safe_free_null(&get->exec_path);
	free_split(get->flags);
	free(command);
}

void	input_reset(t_control *get)
{
	ft_lstclear(&get->commands, (void *)delete_command);
	get->tokens = free_triple_pointer(get->tokens);
	safe_free_null(&get->input);
}

void	safe_free_null(char **string)
{
	if (*string)
	{
		free(*string);
		*string = NULL;
	}
}

int	valid_sequence(t_list *node)
{
	t_command	*command;

	while (node)
	{
		command = (t_command *)node->content;
		if (command->status)
		{
			command->main->status = command->status;
			return (0);
		}
		node = node->next;
	}
	return (1);
}
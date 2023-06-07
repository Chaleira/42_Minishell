/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:33:09 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/07 11:45:31 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	setup_direction(t_command *get)
{
	dup2(get->instream, STDIN_FILENO);
	dup2(get->pipe[1], STDOUT_FILENO);
	close(get->pipe[0]);
}

void	run_input(t_list *node)
{
	t_command	*command;

	while (node)
	{
		// setup_direction(node);
		command = (t_command *)node->content;
		command->execute(command);
		node = node->next;
	}
}

void	execve_aux(t_command *get)
{
	get->id = fork();
	if (!get->id)
	{
		setup_direction(get);
		execve(get->exec_path, get->flags, get->main->envp);
		exit(0);
	}
	else
	{
		// close(get->pipe[1]);
	}
}

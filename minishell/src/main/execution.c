/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:33:09 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/07 14:54:28 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	find_directions(t_list *this)
{
	t_command	*get;

	get = ((t_command *)(this->content));
	if (this->previous)
		get->instream = ((t_command *)(this->previous->content))->pipe[0];
	if (this->next)
	{
		if (pipe(get->pipe) < 0)
			end_shell(*control());
	}
}

void	run_input(t_list *node)
{
	while (node)
	{
		find_directions(node);
		execute_command((t_command *)node->content);
		node = node->next;
	}
}

void	execute_command(t_command *get)
{
	get->id = fork();
	if (!get->id)
	{
		dup2(get->instream, STDIN_FILENO);
		dup2(get->pipe[1], STDOUT_FILENO);
		get->execute(get->exec_path, get->flags, get->main->envp);
		exit(0);
	}
	else
	{
		if (get->instream != get->main->in_out[0])
			close (get->instream);
		if (get->pipe[1] != get->main->in_out[1])
			close(get->pipe[1]);
		wait(0);
	}
}

		// execve(get->exec_path, get->flags, get->main->envp);
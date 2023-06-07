/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:33:09 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/07 19:15:58 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	find_directions(t_list *this)
{
	t_command	*get;

	get = ((t_command *)(this->content));
	if (this->previous)
	{
		get->in_pipe[0] = ((t_command *)(this->previous->content))->out_pipe[0];
		get->in_pipe[1] = ((t_command *)(this->previous->content))->out_pipe[1];
	}
	if (this->next)
	{
		if (pipe(get->out_pipe) < 0)
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
	wait(0);
}

void	execute_command(t_command *get)
{
	get->id = fork();
	if (!get->id)
	{
		close(get->in_pipe[1]);
		close(get->out_pipe[0]);
		dup2(get->in_pipe[0], STDIN_FILENO);
		dup2(get->out_pipe[1], STDOUT_FILENO);
		get->execute(get->exec_path, get->flags, get->main->envp, get);
		end_shell(get->main);
	}
	else
	{
		if (get->in_pipe[0] != get->main->in_out[0])
			close (get->in_pipe[0]);
		if (get->out_pipe[1] != get->main->in_out[1])
			close(get->out_pipe[1]);
	}
}

/* cd primeiro vai verificar se a pasta existe e dar mensagem de erro
depois veriricar se existe mais de um comando e executar de acordo.



*/
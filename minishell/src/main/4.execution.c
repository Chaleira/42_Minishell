/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4execution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:33:09 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/27 09:40:16 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	find_directions(t_list *this)
{
	t_command	*get;

	get = ((t_command *)(this->content));
	if (this->previous && isatty(get->in_pipe[0]))
	{
		get->in_pipe[0] = ((t_command *)(this->previous->content))->out_pipe[0];
		get->in_pipe[1] = ((t_command *)(this->previous->content))->out_pipe[1];
	}
	if (this->next && isatty(get->out_pipe[1]))
	{
		if (pipe(get->out_pipe) < 0)
			end_shell(*control());
	}
}

void	run_input(t_control *get)
{
	int		pid;
	t_list	*node;

	node = get->commands;
	while (node)
	{
		find_directions(node);
		execute_command((t_command *)node->content);
		node = node->next;
	}
	signal(SIGINT, (void *)cut_wait);
	node = get->commands;
	while (node)
	{
		pid = ((t_command *)node->content)->id;
		waitpid(pid, &get->status, 0);
		get->status = WEXITSTATUS(get->status);
		node = node->next;
	}
	signal(SIGINT, control_c);
}
	// ft_printf("status: %i\n", get->status);

void	execute_command(t_command *get)
{
	get->id = fork();
	if (!get->id)
	{
		if (!isatty(get->out_pipe[0]))
			close(get->out_pipe[0]);
		check_dup2(get->in_pipe[0], get->out_pipe[1]);
		get->execute(get->exec_path, get->flags, get->main->envp, get);
		end_shell(get->main);
	}
	else
		safe_close_fd(get->in_pipe[0], get->out_pipe[1]);
}
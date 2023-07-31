/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:38:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/31 11:42:15 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	delete_command(void *command)
{
	t_command	*get;

	get = (t_command *)command;
	safe_free_null(&get->exec_path);
	safe_close_fd(get->in_pipe[0], get->in_pipe[1]);
	safe_close_fd(get->out_pipe[0], get->out_pipe[1]);
	free_split(get->flags);
	free(command);
}

t_command	*new_command(t_control *get)
{
	t_command	*new;

	new = ft_calloc(sizeof(t_command), 1);
	new->main = get;
	new->parse = 1;
	new->in_pipe[0] = get->in_out[0];
	new->out_pipe[1] = get->in_out[1];
	new->execute = do_nothing;
	return (new);
}

int	is_executable(char *check)
{
	struct stat	status;

	bzero(&status, sizeof(struct stat));
	if (!access(check, F_OK))
	{
		if (stat(check, &status))
		{
			ft_printf("minishell: error checking file\n");
			return (-1);
		}
		if (S_ISDIR(status.st_mode))
		{
			ft_printf("minishell: %s: is a directory\n", check);
			return (2);
		}
		if (S_ISREG(status.st_mode) && (status.st_mode & S_IXUSR
			|| status.st_mode & S_IXGRP || status.st_mode & S_IXOTH))
			return (1);
	}
	return (0);
}

void	stop_command(char **split)
{
	if (!split || !*split)
		return ;
	free(split[0]);
	split[0] = ft_strdup("ignore\xFF");
}

void	jump_command(t_command *command, int index)
{
	(void)index;
	command->parse = 0;
	command->execute = do_nothing;
	command->status = PARENT;
}

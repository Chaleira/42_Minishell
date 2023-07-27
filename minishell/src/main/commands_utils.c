/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:38:58 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/27 10:08:14 by rteles-f         ###   ########.fr       */
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

int	is_folder_or_file(char *check)
{
	struct stat	status;

	bzero(&status, sizeof(struct stat));
	stat(check, &status);
	if (S_ISDIR(status.st_mode))
		return (printf("minishell: %s: Is a directory.\n", check));
	else if (!access(check, F_OK) && !S_ISREG(status.st_mode))
		return (ft_printf("minishell: %s: command not found\n", check));
	return (0);
}

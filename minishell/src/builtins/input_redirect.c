/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:27:44 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/10 04:27:44 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	warning_control_d(char *eof, int counter)
{
	eof[ft_strlen(eof) - 1] = 0;
	ft_printf("Minishell: warning: here-document at line %i delimited\
 by end-of-file (wanted `%s')\n", counter, eof);
}

void	here_doc(char *eof, t_command *get)
{
	char	*line;
	int		length;

	if (pipe(get->in_pipe) < 0)
	{
		get->in_pipe[0] = -1;
		return ;
	}
	eof = ft_strjoin(eof, "\n");
	while (eof)
	{
		write (1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		length = ft_strlen(line);
		if (!line)
		{
			warning_control_d(eof, get->main->input_count);
			safe_free_null(&eof);
		}
		else if (!ft_strncmp(line, eof, length))
			safe_free_null(&eof);
		else
			write(get->in_pipe[1], line, length);
		safe_free_null(&line);
	}
	close(get->in_pipe[1]);
}

void	input_redirect(t_command *command, int index)
{
	if (!ft_strncmp(command->terminal[index], "<<", 2))
		here_doc(command->terminal[index + 1], command);
	else
		command->in_pipe[0]
			= open(command->terminal[index + 1], O_RDONLY | 0644);
	if (command->in_pipe[0] < 0)
	{
		command->status = 1;
		command->parse = 0;
		ft_printf("Error opening file: %s\n", command->terminal[index + 1]);
		return ;
	}
	*command->terminal[index + 1] = 0;
}

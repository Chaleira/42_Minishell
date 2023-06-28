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
	ft_printf("\nMinishell: warning: here-document at line %i delimited\
 by end-of-file (wanted `%s')\n", counter, eof);
}

void	stop_heredoc(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	get_input(int fd, int std_in, char *eof, int counter)
{
	char	*line;

	while (eof)
	{
		line = readline(">");
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				warning_control_d(eof, counter);
			else
				dup2(std_in, STDIN_FILENO);
			return ;
		}
		else if (!ft_strncmp(line, eof, -1))
			return ;
		else
			write(fd, line, ft_strlen(line));
		free(line);
	}
}

void	here_doc(char *eof, t_command *get)
{
	if (pipe(get->in_pipe) < 0)
	{
		get->in_pipe[0] = -1;
		return ;
	}
	signal(SIGINT, stop_heredoc);
	get_input(get->in_pipe[1], get->main->in_out[0], eof, get->main->input_count);
	signal(SIGINT, control_c);
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

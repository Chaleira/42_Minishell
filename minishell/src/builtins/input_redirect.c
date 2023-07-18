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
	ft_printf("Minishell: warning: here-document at line %i delimited \
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

	while (true)
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
		{
			ft_stradd(&line, "\n");
			write(fd, line, ft_strlen(line));
		}
		safe_free_null(&line);
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
	command->in_pipe[0] = open(command->terminal[index + 1], O_RDONLY | 0644);
	if (command->in_pipe[0] < 0)
	{
		command->main->status = 1;
		command->execute = do_nothing;
		jump_command(command, 0);
		ft_printf("Minishell: %s: No such file or directory\n", command->terminal[index + 1]);
	}
	*command->terminal[index + 1] = 0;
}

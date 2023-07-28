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

char	**find_eof(char *eof, char **matrix, int counter)
{
	char	*line;

	line = readline(">");
	if (line && ft_stradd(&line, "\n") && !ft_strncmp(line, eof, -1))
	{
		*eof = FOUND;
		safe_free_null(&line);
	}
	if (!line || !eof)
		matrix = ft_calloc(sizeof(char *), counter + 1);
	else
	{
		matrix = find_eof(eof, matrix, (counter + 1));
		matrix[counter] = line;
	}
	return (matrix);
}

char	**here_doc(char *eof, t_control *get)
{
	char	**matrix;

	signal(SIGINT, stop_heredoc);
	matrix = find_eof(eof, NULL, 0);
	if (*eof != FOUND)
	{
		if (isatty(STDIN_FILENO))
			warning_control_d(eof, get->input_count);
		else
		{
			dup2(get->in_out[0], STDIN_FILENO);
			matrix = free_split(matrix);
		}
	}
	signal(SIGINT, control_c);
	return (matrix);
}

void	input_redirect(t_command *command, int index)
{
	command->in_pipe[0]
		= open(command->terminal[index + 1], O_RDONLY | 0644);
	command->in_pipe[0] = open(command->terminal[index + 1], O_RDONLY | 0644);
	if (command->in_pipe[0] < 0)
	{
		command->main->status = 1;
		command->execute = do_nothing;
		jump_command(command, 0);
		ft_printf("Minishell: %s: No such file or directory\n",
			command->terminal[index + 1]);
	}
	*command->terminal[index + 1] = 0;
}

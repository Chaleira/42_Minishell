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

#define COUNTER 2
#define PIPE 1

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

void	find_eof(char *eof, t_command *command, int expand)
{
	char	*line;

	while (eof)
	{
		line = readline("> ");
		if (expand && line)
			line = input_expand(line, command->main->envp, 0);
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				warning_control_d(eof, command->main->input_count);
			else
				dup2(command->main->in_out[0], STDIN_FILENO);
			eof = NULL;
		}
		else if (!ft_strcmp(line, eof))
			eof = NULL;
		else
		{
			write(command->in_pipe[1], line, ft_strlen(line));
			write(command->in_pipe[1], "\n", 1);
		}
		safe_free_null(&line);
	}
}

void	here_doc(t_command *get, char *eof)
{
	int	expand;

	expand = 1;
	if (find_pair(eof, "\'\""))
		expand = 0;
	remove_pair(eof, "\'\"");
	if (pipe(get->in_pipe) < 0)
	{
		get->in_pipe[0] = -1;
		return ;
	}
	signal(SIGINT, stop_heredoc);
	find_eof(eof, get, expand);
	signal(SIGINT, control_c);
	close(get->in_pipe[1]);
}

void	input_redirect(t_command *command, int index)
{
	if (*(short *)command->terminal[index] == *(short *)"<<")
		here_doc(command, command->terminal[index + 1]);
	else
		command->in_pipe[0]
			= open(command->terminal[index + 1], O_RDONLY | 0644);
	if (command->in_pipe[0] < 0)
	{
		command->main->status = 1;
		jump_command(command, 0);
		ft_printf("Minishell: %s: No such file or directory\n",
			command->terminal[index + 1]);
	}
	command->terminal[index + 1] = 0;
}
// char	*catch_one(t_control *get)
// {
// 	char	*line;

// 	line = "start";
// 	signal(SIGINT, stop_heredoc);
// 	while (line)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			if (isatty(STDIN_FILENO))
// 				end_shell(get);
// 			else
// 			{
// 				dup2(get->in_out[0], STDIN_FILENO);
// 				break ;
// 			}
// 		}
// 		else if (!*line)
// 			safe_free_null(&line);
// 		else
// 			break;
// 	}
// 	signal(SIGINT, control_c);
// 	return (line);
// }
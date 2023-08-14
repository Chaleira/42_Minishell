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

void	stop_heredoc(int signal)
{
	(void)signal;
	(*control())->status = 130;
	close(STDIN_FILENO);
	write(1, "\n", 1);
}

void	close_doc_pipes(char ***tokens)
{
	int	index;

	index = 0;
	while (tokens && *tokens && (*tokens)[index])
	{
		if (*(short *)(*tokens)[index] == *(short *)"<<")
		{
			if (!isatty(((int *)(*tokens)[index + 1])[0]))
				close(((int *)(*tokens)[index + 1])[0]);
			if (!isatty(((int *)(*tokens)[index + 1])[1]))
				close(((int *)(*tokens)[index + 1])[1]);
		}
		index++;
	}
	if (tokens && *(tokens + 1))
		close_doc_pipes(tokens + 1);
}

void	forced_eof(t_control *get, char* eof, int *in_pipe)
{
	char	*message;

	if (isatty(STDIN_FILENO))
	{
		message = ft_strjoin("Minishell: warning: here-document at line ",
								sttc_itoa(get->input_count));
		ft_stradd(&message, " delimited by end-of-file (wanted `");
		ft_stradd(&message, eof);
		ft_stradd(&message, "')\n");
		write (2, message, ft_strlen(message));
		free(message);
	}
	else
	{
		dup2(get->in_out[0], STDIN_FILENO);
		close(in_pipe[0]);
		close_doc_pipes(get->tokens);
		get->tokens = free_split((char **)get->tokens);
		input_reset(get);
	}
}

int	find_eof(int fd, char *eof, int expand, char **envp)
{
	char	*line;

	while (eof)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (!ft_strcmp(line, eof))
			eof = NULL;
		else
		{
			if (expand)
				line = input_expand(line, envp, 0);
			write(fd, ft_stradd(&line, "\n"), ft_strlen(line) + 1);
		}
		safe_free_null(&line);
	}
	return (1);
}

int	new_pipe(int **newpipe, t_control *get)
{
	*newpipe = ft_calloc(sizeof(int), 2);
	if (pipe(*newpipe) < 0)
	{
		free(*newpipe);
		write (2, "minishell: error in pipe usage\n", 32);
		input_reset(get);
		return (0);
	}
	return (1);
}

int	*here_doc(t_control *get, char *eof)
{
	int	expand;
	int	*in_pipe;

	if (!new_pipe(&in_pipe, get))
		return (NULL);
	expand = !find_pair(eof, "\'\"");
	remove_pair(eof, "\'\"");
	signal(SIGINT, stop_heredoc);
	if (!find_eof(in_pipe[1], eof, expand, get->envp))
		forced_eof(get, eof, in_pipe);
	signal(SIGINT, control_c);
	close(in_pipe[1]);
	if (read(in_pipe[0], 0, 0) < 0)
		safe_free_null((char **)&in_pipe);
	return (in_pipe);
}

/*
Problems:

control C giving 2 enters after closing and opening the terminal

Expansion
*/
void	input_redirect(t_command *command, int index)
{
	if (*(short *)command->terminal[index] == *(short *)"<<")
		*(long *)command->in_pipe = *(long *)command->terminal[index + 1];
	else
		command->in_pipe[0]
			= open(command->terminal[index + 1], O_RDONLY | 0644);
	if (command->in_pipe[0] < 0)
	{
		command->main->status = 1;
		jump_command(command, 0);
		write(2, "minishell: ", 12);
		write(2, command->terminal[index + 1],
				ft_strlen(command->terminal[index + 1]));
		write(2, ": No such file or directory\n", 29);
	}
	if (command->terminal)
		*command->terminal[index + 1] = 0;
}
// int	here_doc(t_command *command, char *eof)
// {
// 	int	expand;

// 	if (pipe(command->in_pipe) < 0)
// 		return (-1);
// 	command->main->status = 0;
// 	expand = !!find_pair(eof, "\'\"");
// 	remove_pair(eof, "\'\"");
// 	signal(SIGINT, stop_heredoc);
// 	if (!find_eof(eof, expand, command))
// 	{
// 		if (isatty(STDIN_FILENO))
// 			warning_control_d(eof, command->main->input_count);
// 		else
// 		{
// 			jump_command(command, 0);
// 			dup2(command->main->in_out[0], STDIN_FILENO);
// 		}
// 		command->terminal = 0;
// 	}
// 	signal(SIGINT, control_c);
// 	close(command->in_pipe[1]);
// 	return (command->in_pipe[0]);
// }

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
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

// void	warning_control_d(char *eof, int counter)
// {
// 	ft_printf("Minishell: warning: here-document at line %i delimited 
// by end-of-file (wanted `%s')\n", counter, eof);
// }

// void	find_eof(char *eof, t_command *command, int expand)
// {
// 	char	*line;

// 	while (eof)
// 	{
// 		line = readline("> ");
// 		if (expand && line)
// 			line = input_expand(line, command->main->envp, 0);
// 		if (!line)
// 		{
// 			if (isatty(STDIN_FILENO))
// 				warning_control_d(eof, command->main->input_count);
// 			else
// 				dup2(command->main->in_out[0], STDIN_FILENO);
// 			eof = NULL;
// 		}
// 		else if (!ft_strcmp(line, eof))
// 			eof = NULL;
// 		else
// 			write(command->in_pipe[1], ft_stradd(&line, "\n"), ft_strlen(line) + 1);
// 		safe_free_null(&line);
// 	}
// }

// int	find_eof(char *eof, int expand, t_command *command)
// {
// 	char	*line;

// 	while (eof)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			return (0);
// 		if (expand)
// 			line = input_expand(line, command->main->envp, 0);
// 		else if (!ft_strcmp(line, eof))
// 			eof = NULL;
// 		else
// 			write(command->in_pipe[1], ft_stradd(&line, "\n"), ft_strlen(line) + 1);
// 		safe_free_null(&line);
// 	}
// 	return (1);
// }

void	stop_heredoc(int signal)
{
	(void)signal;
	(*control())->status = 130;
	close(STDIN_FILENO);
	write(1, "\n", 1);
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
		if (expand)
			line = input_expand(line, envp, 0);
		else if (!ft_strcmp(line, eof))
			eof = NULL;
		else
			write(fd, ft_stradd(&line, "\n"), ft_strlen(line) + 1);
		safe_free_null(&line);
	}
	return (1);
}

int	*here_doc(t_control *get, char *eof)
{
	int	expand;
	int	*in_pipe;

	in_pipe = ft_calloc(sizeof(int), 2);
	if (pipe(in_pipe) < 0)
	{
		write (2, "minishell: error in pipe usage\n", 32);
		input_reset(get);
		return (NULL);
	}
	expand = !!find_pair(eof, "\'\"");
	remove_pair(eof, "\'\"");
	signal(SIGINT, stop_heredoc);
	if (!find_eof(in_pipe[1], eof, expand, get->envp))
		forced_eof(get, eof, in_pipe);
	signal(SIGINT, control_c);
	close(in_pipe[1]);
	// in_pipe[0] = open("/dev/null", O_RDONLY | 0644);
	if (read(in_pipe[0], 0, 0) < 0)
		return (NULL);
	return (in_pipe);
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

/*
Problems:

control C giving 2 enters after closing and opening the terminal

Expansion

bonus with control C in the heredoc - bonus executes the command first and then the heredoc is opened
dont know how I going to make the heredoc come first or hold the bonus execution till later.
probably better to open the docs first.
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
		write(2, command->terminal[index + 1], ft_strlen(command->terminal[index + 1]));
		write(2, ": No such file or directory\n", 29);
	}
	if (command->terminal)
		*command->terminal[index + 1] = 0;
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
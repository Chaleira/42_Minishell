/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:43:59 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/06 17:44:51 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	catch_input(t_control *get)
{
	const char	*line;

	line = NULL;
	(void)get;
	write (1, "Minishell>$ ", 12);
	// get->input = readline(line);
	get->input = get_next_line(0);
	if (get->input)
		get->input[ft_strlen(get->input) - 1] = 0;
}

void	input_reset(t_control *get)
{
	ft_lstclear(&get->commands, (void *)delete_command);
	free_shellsplit(get->pieces);
	if (get->input)
	{
		free(get->input);
		get->input = NULL;
	}
}

void	delete_command(void *command)
{
	t_command	*get;

	get = (t_command *)command;
	free_split(get->flags);
	if (get->aux)
	{
		free(get->aux);
		get->aux = NULL;
	}
	if(get->exec_path)
	{
		free(get->exec_path);
		get->exec_path = NULL;
	}
	//CUIDADO COM ESSA PORRA
	// close(get->pipe[0]);
	// close(get->pipe[1]);
	// close(get->instream);
	free(command);
	command = NULL;
}

void	end_shell(t_control *get)
{
	input_reset(get);
	free_split(get->pieces);
}

int	main(int argc, char **argv, char **envp)
{
	static t_control	get;

	(void)argv;
	(void)argc;
	setup(&get, envp);
	while (true)
	{
		catch_input(&get);
		normalize_input(&get);
		structure_commands(&get);
		run_input(get.commands);
		input_reset(&get);
	}
	return (1);
}

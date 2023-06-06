/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:43:59 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/06 17:32:03 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_unsplit(char **split, int posize)
{
	char	*line;
	int		i;

	if (*split)
		line = ft_unsplit((split + 1), posize + ft_strlen(*split) + 1);
	else
	{
		line = ft_calloc(sizeof(char), posize + 2);
		line[posize] = '\n';
		return (line);
	}
	i = 0;
	while ((*split)[i])
		line[posize++] = (*split)[i++];
	line[posize] = ' ';
	return (line);
}

void	printf_input(t_control *get)
{
	ft_printf("\nInput-->\n");
	for (int i = 0; get->pieces[i]; i++)
	{
		ft_printf("command %i->\n", i);
		for (int j = 0; get->pieces[i][j]; j++)
			ft_printf("%s\n", get->pieces[i][j]);
	}
	ft_printf("end.\n");
}

void	catch_input(t_control *get)
{
	// const char	*line;

	// line = NULL;
	(void)get;
	write (1, "Minishell>$ ", 12);
	// get->input = readline(line);
	get->input = get_next_line(0);
	if (get->input)
		get->input[ft_strlen(get->input) - 1] = 0;
}

void	input_reset(t_control *get)
{
	wait(0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:43:59 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/08 16:23:14 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	**control(void)
{
	static void	*get;

	return (&get);
}

void	catch_input(t_control *get)
{
	// const char	*line;

	// line = NULL;
	(void)get;
	wait(0);
	write (1, "\033[31mMinishell\033[0;33m ✗ \033[0m", 31);
	// get->input = readline(line);
	get->input = get_next_line(0);
	if (get->input)
		get->input[ft_strlen(get->input) - 1] = 0;
}

int	main(int argc, char **argv, char **envp)
{
	static t_control	get;

	(void)argv;
	(void)argc;
	setup(&get, envp);
	while (!get.end)
	{
		catch_input(&get);
		normalize_input(&get);
		structure_commands(&get);
		run_input(get.commands);
		input_reset(&get);
	}
	return (1);
}

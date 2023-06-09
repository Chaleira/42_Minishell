/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:43:59 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/09 18:27:03 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_control	**control(void)
{
	static t_control	*get;

	return (&get);
}

void	catch_input(t_control *get)
{
	// char	*line;
	char	*new;

	// line = NULL;
	(void)get;
	wait(0);
	new = ft_strrchr(get->pwd, '/');
	ft_printf("\033[1m\033[31mMinishell \033[0m\033[34m%s \033[0;33m✗ \033[0m", (new + 1));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:43:59 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/27 18:58:50 by plopes-c         ###   ########.fr       */
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
	get->input = readline(get->prompt);
	if (!get->input)
		control_d(0);
	else
		add_history(get->input);
	rl_on_new_line();
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
		run_input(&get);
		input_reset(&get);
	}
	return (get.status);
}

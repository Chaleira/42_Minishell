/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:43:59 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/30 15:41:05 by rteles-f         ###   ########.fr       */
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
		control_d(get);
	else
	{
		get->input_count++;
		if (*get->input)
			add_history(get->input);
	}
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

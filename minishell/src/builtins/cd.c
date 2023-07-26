/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:31:03 by plopes-c          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/26 14:30:05 by plopes-c         ###   ########.fr       */
=======
/*   Updated: 2023/07/26 15:28:33 by rteles-f         ###   ########.fr       */
>>>>>>> f8ae893e1431675a2a4422d47376da76e090036e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
static void	cd_execute(char *str, char )
=======
 void	cd_execute(char *str, char **directory, char **envp, t_command *get)
>>>>>>> f8ae893e1431675a2a4422d47376da76e090036e
{
	(void)str;
	(void)envp;
	if (!directory || !*directory)
		return ;
	if (chdir(*directory))
	{
		ft_printf("minishell: cd: %s: Not a directory\n", *directory);
		get->main->status = 1;
	}
	free(get->main->prompt);
	get->main->prompt = get_prompt();
	get->main->status = 0;
}

int	execute_now(t_command *get)
{
	int	index;

	index = 0;
	while (get->main->tokens[index] != get->terminal)
		index++;
	if (get->main->tokens[index + 1]
		&& !ft_strncmp(get->main->tokens[index + 1][0], "|", 2))
		return (0);
	else if (get->main->tokens[index] && !ft_strncmp(get->main->tokens[index][0], "|", 2))
		return (0);
	return (1);
}

void	cd_prepare(t_command *command, int index)
{
	int	args;

	args = 0;
	while (command->terminal[index + args]
		&& !split_case(command->terminal[index + args]))
		args++;
	if (args == 1)
		return ;
	if (args > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		command->status = 1;
		return ;
	}
	command->flags = copy_shellsplit(&command->terminal[index + 1]);
	command->terminal[index + 1][0] = 0;
	command->execute = (void *)cd_execute;
	if (execute_now(command))
		command->status = PARENT;
}

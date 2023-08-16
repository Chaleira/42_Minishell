/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:31:03 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/16 21:21:53 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_execute(char *current, char **directory, char **envp, t_command *get)
{
	char	*pwd;

	(void)envp;
	if (!directory || !*directory)
		return ;
	if (chdir(*directory))
	{
		ft_printf("minishell: cd: %s: Not a directory\n", *directory);
		get->main->status = 1;
		return ;
	}
	free(get->main->prompt);
	get->main->prompt = get_prompt();
	get->main->status = 0;
	pwd = getcwd(NULL, 0);
	change_env_variable("OLDPWD", &(env_var("PWD", (*control())->envp)[0][4]));
	change_env_variable("PWD", pwd);
	free(pwd);
	free(current);
}

void	cd_prepare(t_command *command, int index)
{
	int	args;

	args = 0;
	while (command->terminal[index + args]
		&& !split_case(command->terminal[index + args]))
		args++;
	if (args == 1)
		command->flags = ft_split(command->main->home, ' ');
	if (args > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		command->status = 1;
		input_reset(command->main);
		return ;
	}
	if (args == 2)
	{
		command->flags = copy_shellsplit(&command->terminal[index + 1]);
		command->terminal[index + 1][0] = 0;
	}
	if (!command->status)
		command->execute = (void *)cd_execute;
	if (execute_now(command))
		command->status = PARENT;
}

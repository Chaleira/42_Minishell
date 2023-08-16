/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:54:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/16 21:26:14 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd_prepare(t_command *command, int index)
{
	(void)index;
	command->exec_path = getcwd(NULL, 0);
	ft_stradd(&command->exec_path, "\n");
	if (!command->status)
		command->execute = builtin_execute;
}

void	update_pwd(t_control *get)
{
	char	**pwd;
	char	*cwd;

	get->home = ft_strdup(&((env_var("HOME", (*control())->envp))[0][5]));
	pwd = get_envaddress((*control())->envp, "PWD");
	if (!pwd)
	{
		cwd = getcwd(NULL, 0);
		change_env_variable("PWD", cwd);
		if (cwd)
			free(cwd);
		return ;
	}	
}

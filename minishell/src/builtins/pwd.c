/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:54:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/17 11:34:45 by plopes-c         ###   ########.fr       */
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
	char	**envar;
	char	*cwd;

	envar = get_envaddress(get->envp, "HOME");
	if (envar && *envar)
		get->home = ft_strdup(&(*envar)[5]);
	envar = get_envaddress(get->envp, "PWD");
	if (!envar)
	{
		cwd = getcwd(NULL, 0);
		change_env_variable("PWD", cwd);
		if (cwd)
			free(cwd);
		return ;
	}
}

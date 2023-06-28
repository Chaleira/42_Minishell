/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:31:03 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/28 09:12:59 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_execute(char *str)
{
	if (!str)
		return ;
	if (chdir(str))
	{
		ft_printf("minishell: cd: %s: Not a directory\n", str);
		(*control())->status = 1;
		return ;
	}
	free((*control())->prompt);
	(*control())->prompt = get_prompt();
	(*control())->status = 0;
}

static int	execute_now(t_control *get)
{
	int	index;

	index = ft_lstsize(get->commands);
	if (get->tokens[index + 1] && !ft_strncmp(get->tokens[index + 1][0], "|", 2))
		return (0);
	else if (get->tokens[index] && !ft_strncmp(get->tokens[index][0], "|", 2))
		return (0);
	return (1);
}

/* If the folder is changed here, it will compromise next arguments
such as redirections, the change of directory has to be done
at the end of the command structure - change to parent execution
later, or keep this mess*/
void	cd_prepare(t_command *command, int index)
{
	int	args;

	args = 0;
	while (command->terminal[index + args] && !split_case(command->terminal[index + args]))
		args++;
	if (args > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		command->status = 1;
		return ;
	}
	command->exec_path = ft_strdup(command->terminal[index + 1]);
	command->terminal[index + 1][0] = 0;
	command->execute = (void *)cd_execute;
	if (execute_now(command->main))
		command->status = PARENT;
}

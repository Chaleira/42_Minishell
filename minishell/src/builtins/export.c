/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:56:31 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/08 19:12:45 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_prepare(t_command *command, int index)
{
	(void)index;
	command->exec_path = ft_unsplit(command->main->envp, 0, '\n');
	command->execute = export_execute;
}

void	export_execute(char *print)
{
	ft_printf("declare -x %s", print);
}

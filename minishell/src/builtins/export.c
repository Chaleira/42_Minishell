/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:56:31 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/10 04:30:22 by rteles-f         ###   ########.fr       */
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
	char	**split;
	int		i;

	split = ft_split(print, '\n');
	i = 0;
	while (split[i])
	{
		ft_printf("declare -x %s\n", split[i]);
		i++;
	}
}

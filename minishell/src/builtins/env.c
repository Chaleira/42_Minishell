/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:59:05 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/12 18:17:58 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_prepare(t_command *command, int index)
{
	(void)index;
	command->exec_path = ft_unsplit(command->main->envp, 0, '\n');
	command->execute = builtin_execute;
}

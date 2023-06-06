/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:19 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/06 17:41:10 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(t_command *command, int index)
{
	if (command->terminal[index + 1])
	{
		command->aux = ft_unsplit(&command->terminal[index + 1], 0);
		while (command->terminal[++index])
			*command->terminal[index] = 0;
	}
	else
	{
		command->aux = ft_calloc(sizeof(char), 2);
		command->aux[0] = '\n';
	}
	printf("aux: %s\n", command->aux);
	command->execute = do_nothing;
}
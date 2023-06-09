/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_direct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:14:52 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/09 17:50:35 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	output_direct(t_command *command, int index)
{
	int	fd;
	
	(void)fd;
	if (command->terminal[index + 2])
	{
		command->valid = 0;
		return ;
	}
	fd = open(command->terminal[index + 1], O_CREAT | O_RDWR);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:59:29 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/06 12:22:34 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_command(void *command)
{
	t_command *get;
	
	get = command;
	free_split(get->flags);
	free_split(get->terminal);
	if (get->aux)
		free(get->aux);
	close(get->instream);
	close(get->pipe[0]);
	close(get->pipe[1]);
	free(get);
}

void	free_split(char **matrix)
{
	int i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

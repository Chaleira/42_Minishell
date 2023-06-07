/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:34:23 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/07 10:48:41 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	end_shell(t_control *get)
{
	input_reset(get);
	free_split(get->paths);
	exit(0);
}

void	delete_command(void *command)
{
	t_command	*get;

	get = (t_command *)command;
	free_split(get->flags);
	safe_free_null(&get->aux);
	safe_free_null(&get->exec_path);
	free(command);
	//CUIDADO COM ESSA PORRA
	// close(get->pipe[0]);
	// close(get->pipe[1]);
	// close(get->instream);
}

void	input_reset(t_control *get)
{
	ft_lstclear(&get->commands, (void *)delete_command);
	free_shellsplit(&get->pieces);
	safe_free_null(&get->input);
}

void	safe_free_null(char **string)
{
	if (*string)
	{
		free(*string);
		*string = NULL;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:13:06 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/25 18:25:02 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_execute(char *print)
{
	if (print)
		if (print)
		ft_printf("%s", print);
}

void	stop_command(char **split)
{
	free(split[0]);
	split[0] = ft_strdup("ignore\xFF");
}

void	jump_command(t_command *command, int index)
{
	(void)index;
	command->parse = 0;
	command->status = PARENT;
}

void	do_nothing(void)
{
	return ;
}
// void	printf_input(t_control *get)
// {
// 	ft_printf("\nInput-->\n");
// 	for (int i = 0; get->tokens[i]; i++)
// 	{
// 		ft_printf("command %i->\n", i);
// 		for (int j = 0; get->tokens[i][j]; j++)
// 			ft_printf("%s\n", get->tokens[i][j]);
// 	}
// 	ft_printf("end.\n");
// }

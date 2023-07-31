/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:13:06 by rteles-f          #+#    #+#             */
/*   Updated: 2023/07/31 09:46:03 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_now(t_command *get)
{
	int	index;

	index = 0;
	while (get->main->tokens[index] != get->terminal)
		index++;
	if (get->main->tokens[index + 1]
		&& !ft_strncmp(get->main->tokens[index + 1][0], "|", 2))
		return (0);
	else if (get->main->tokens[index]
		&& !ft_strncmp(get->main->tokens[index][0], "|", 2))
		return (0);
	return (1);
}

void	builtin_execute(char *print)
{
	if (print)
		ft_printf("%s", print);
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

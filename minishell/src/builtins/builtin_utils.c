/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:13:06 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/15 14:02:57 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_execute(char *print)
{
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

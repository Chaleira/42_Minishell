/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:13:06 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/12 12:41:32 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_execute(char *print)
{
	ft_printf("%s", print);
}

// void	printf_input(t_control *get)
// {
// 	ft_printf("\nInput-->\n");
// 	for (int i = 0; get->pieces[i]; i++)
// 	{
// 		ft_printf("command %i->\n", i);
// 		for (int j = 0; get->pieces[i][j]; j++)
// 			ft_printf("%s\n", get->pieces[i][j]);
// 	}
// 	ft_printf("end.\n");
// }

void	do_nothing(void)
{
	return ;
}

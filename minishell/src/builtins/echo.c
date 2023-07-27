/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:58:19 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/29 11:27:40 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *string)
{
	int	i;

	if (!string || *string != '-')
		return (0);
	i = 1;
	while (string[i] && string[i] == 'n')
		i++;
	if (string[i])
		return (0);
	return (1);
}

static void	echo_execute(char *a, char **print)
{
	int	i;
	int	flag;

	(void)a;
	flag = check_flag(*print);
	i = flag;
	while (print[i])
	{
		ft_printf("%s", print[i]);
		if (print[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!flag)
		ft_printf("\n");
	(*control())->status = 0;
}

void	echo_prepare(t_command *command, int index)
{
	command->flags = copy_shellsplit(&command->terminal[index + 1]);
	while (command->terminal[index] && !split_case(command->terminal[index]))
		*command->terminal[index++]= 0;
	command->execute = echo_execute;
}

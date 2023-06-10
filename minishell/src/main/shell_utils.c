/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:13:06 by rteles-f          #+#    #+#             */
/*   Updated: 2023/06/10 03:59:36 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**copy_shellsplit(char **split)
{
	char	**new;
	int		counter;

	counter = 0;
	while (split[counter] && !split_case(split[counter]))
		counter++;
	new = ft_calloc(sizeof(char *), counter + 1);
	counter = 0;
	while (split[counter] && !split_case(split[counter]))
	{
		new[counter] = ft_strdup(split[counter]);
		counter++;
	}
	return (new);
}

void	builtin_execute(char *print)
{
	ft_printf("%s", print);
}

void	free_split(char **split)
{
	int	i;

	if (split)
	{
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		split = 0;
	}
}

void	printf_input(t_control *get)
{
	ft_printf("\nInput-->\n");
	for (int i = 0; get->pieces[i]; i++)
	{
		ft_printf("command %i->\n", i);
		for (int j = 0; get->pieces[i][j]; j++)
			ft_printf("%s\n", get->pieces[i][j]);
	}
	ft_printf("end.\n");
}

void	do_nothing(void)
{
	return ;
}

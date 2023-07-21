/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:56:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/07/20 21:58:26 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse(char **split)
{
	int	i;
	
	i = 0;
	while (split && split[i])
	{
		if (split[i][0] == ';')
		{
			if (split[i + 1] && split[i + 1][0] == ';')
			{
				ft_printf("minishell: syntax error near unexpected token '%s'\n", split[i]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int check_char(char *str)
{
	int	i;
	int count;
	
	count = 0;
	i = 0;
	while (str && str[i])
	{
		count += (str[i] == '"');
		i++;
	}
	if (count == 1)
		return (0);
	return (1);
}

void print_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		ft_printf("%s\n", split[i]);
		i++;
	}
	ft_printf("END PRINT SPlIT\n");
}

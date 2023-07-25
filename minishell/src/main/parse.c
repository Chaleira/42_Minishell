/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:56:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/07/21 11:38:10 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse(char **split)
{
	static char *check_cases[] = {
		">", ">>", "<", "<<", ";", "|"}
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

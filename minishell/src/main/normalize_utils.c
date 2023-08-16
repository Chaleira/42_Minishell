/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:16:41 by plopes-c          #+#    #+#             */
/*   Updated: 2023/08/16 19:18:38 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_end_of_command(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (1);
	return (0);
}

int	count_cases(char **string)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!string)
		return (0);
	while (string[i])
	{
		if (is_end_of_command(string[i][0]))
			count++;
		i++;
	}
	return (count);
}

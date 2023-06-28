/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:56:24 by plopes-c          #+#    #+#             */
/*   Updated: 2023/06/28 17:28:36 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_char(char *str, char c);

void	parse(char **split)
{
	int	j;
	int	i;

	j = 0;
	while (split && split[j])
	{
		i = 0;
		while (split && split[j][i])
		{
			i += !!(ignore_quotes(&split[j][i])) + ignore_quotes(&split[j][i]);
			
			i++;
		}
		j++;
		ft_printf("\n");
	}
}

int	count_char(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

// int main (void)
// {
// 	char *split[3];

// 	split[0] = "abc\"abc";
// 	split[1] = "def \"123\"def";
// 	split[2] = NULL;
// 	ft_printf("before: %s\n", split[0]);
// 	ft_printf("before: %s\n", split[1]);
// 	// parse(split);
// }
